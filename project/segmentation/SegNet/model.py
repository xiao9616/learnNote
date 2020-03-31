# encoding: utf-8

# @author: wenxuan
# @contact: 749935253@qq.com
# @software: PyCharm
# @file: model.py
# @time: 19-5-6 下午4:23


from Utils import *
from Inputs import *
import numpy as np
import time
from datetime import datetime
import os

MOVING_AVERAGE_DECAY = 0.9999  # The decay to use for the moving average.
NUM_EPOCHS_PER_DECAY = 350.0  # Epochs after which learning rate decays.
LEARNING_RATE_DECAY_FACTOR = 0.1  # Learning rate decay factor.

INITIAL_LEARNING_RATE = 0.001  # Initial learning rate.
EVAL_BATCH_SIZE = 5
BATCH_SIZE = 5
# for CamVid
IMAGE_HEIGHT = 360
IMAGE_WIDTH = 480
IMAGE_DEPTH = 3

NUM_CLASSES = 12
NUM_EXAMPLES_PER_EPOCH_FOR_TRAIN = 367
NUM_EXAMPLES_PER_EPOCH_FOR_TEST = 101
NUM_EXAMPLES_PER_EPOCH_FOR_EVAL = 1
TEST_ITER = NUM_EXAMPLES_PER_EPOCH_FOR_TEST / BATCH_SIZE


def inference(images, labels, batch_size, phase_train):
    """
    设置网络结构
    :param images:输入图片
    :param labels: 标签
    :param batch_size:batch大小
    :param phase_train: 是否训练参数
    :return: loss和前向输出
    """
    # LRN(Local Response Normalization） 局部响应归一化
    # 模仿生物的神经的侧抑制作用使得响应高的地方更加大，提高了模型的泛化能力，同时近似归一化
    norm1 = tf.nn.lrn(images, depth_radius=5, bias=1.0, alpha=0.0001, beta=0.75, name='norm1')

    # 卷积层
    conv1 = conv_layer_with_bn(norm1, [7, 7, images.get_shape().as_list()[3], 64], phase_train, name="conv1")

    # 池化层带有最大池化索引
    pool1, pool1_indices = tf.nn.max_pool_with_argmax(conv1, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME',
                                                      name='pool1')

    conv2 = conv_layer_with_bn(pool1, [7, 7, 64, 64], phase_train, name='conv2')

    pool2, pool2_indices = tf.nn.max_pool_with_argmax(conv2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME',
                                                      name='pool2')
    conv3 = conv_layer_with_bn(pool2, [7, 7, 64, 64], phase_train, name='conv3')

    pool3, pool3_indices = tf.nn.max_pool_with_argmax(conv3, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME',
                                                      name='pool3')
    conv4 = conv_layer_with_bn(pool3, [7, 7, 64, 64], phase_train, name='conv4')

    pool4, pool4_indices = tf.nn.max_pool_with_argmax(conv4, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME',
                                                      name='pool4')
    "卷积编码结束，开始解码"

    upsample4 = deconv_layer(pool4, [2, 2, 64, 64], [batch_size, 45, 60, 64], 2, name='up4')

    conv_decode4 = conv_layer_with_bn(upsample4, [7, 7, 64, 64], phase_train, False, name='conv_decode4')

    upsample3 = deconv_layer(conv_decode4, [2, 2, 64, 64], [batch_size, 90, 120, 64], 2, 'up3')

    conv_decode3 = conv_layer_with_bn(upsample3, [7, 7, 64, 64], phase_train, False, name='conde_decode3')

    upsample2 = deconv_layer(conv_decode3, [2, 2, 64, 64], [batch_size, 180, 240, 64], 2, 'up2')

    conv_decode2 = conv_layer_with_bn(upsample2, [7, 7, 64, 64], phase_train, False, name='conv_decode2')

    upsample1 = deconv_layer(conv_decode2, [2, 2, 64, 64], [batch_size, 360, 480, 64], 2, name='up1')

    conv_decode1 = conv_layer_with_bn(upsample1, [7, 7, 64, 64], phase_train, False, name='conv_decode1')

    "解码结束，开始分类"

    with tf.variable_scope('conv_classifier') as scope:
        kernel = variable_with_weight_decay('weights', shape=[1, 1, 64, NUM_CLASS], initializer=msra_initializer(1, 64),
                                            wd=0.0005)
        conv = tf.nn.conv2d(conv_decode1, kernel, [1, 1, 1, 1], padding='SAME')
        biases = variable_with_weight_decay("biases", [NUM_CLASS], tf.constant_initializer(0.0))
        conv_classifier = tf.nn.bias_add(conv, biases)

    "定义损失"

    logit = conv_classifier
    loss = cal_loss(conv_classifier, labels)
    return loss, logit


def train(total_loss, global_step):
    total_sample = 274
    num_batches_per_epoch = 274 / 1
    """ fix lr """
    lr = INITIAL_LEARNING_RATE
    loss_averages_op = add_loss_summaries(total_loss)

    # Compute gradients.
    with tf.control_dependencies([loss_averages_op]):
        opt = tf.train.AdamOptimizer(lr)
        grads = opt.compute_gradients(total_loss)
    apply_gradient_op = opt.apply_gradients(grads, global_step=global_step)

    # Add histograms for trainable variables.
    for var in tf.trainable_variables():
        tf.summary.histogram(var.op.name, var)

    # Add histograms for gradients.
    for grad, var in grads:
        if grad is not None:
            tf.summary.histogram(var.op.name + '/gradients', grad)

    # Track the moving averages of all trainable variables.
    variable_averages = tf.train.ExponentialMovingAverage(
        MOVING_AVERAGE_DECAY, global_step)
    variables_averages_op = variable_averages.apply(tf.trainable_variables())

    with tf.control_dependencies([apply_gradient_op, variables_averages_op]):
        train_op = tf.no_op(name='train')

    return train_op


def training(FLAGS, is_finetune=False):
    max_steps = FLAGS.max_steps
    batch_size = FLAGS.batch_size
    train_dir = FLAGS.log_dir
    image_dir = FLAGS.image_dir
    val_dir = FLAGS.val_dir
    finetune_ckpt = FLAGS.finetune
    image_w = FLAGS.image_w
    image_h = FLAGS.image_h
    image_c = FLAGS.image_c
    image_filenames, label_filenames = get_filename_list(image_dir)
    val_image_filenames, val_label_filenames = get_filename_list(val_dir)
    startstep = 0 if not is_finetune else int(FLAGS.finetune.split('-')[-1])
    with tf.Graph().as_default():
        train_data_node = tf.placeholder(tf.float32, shape=[batch_size, image_h, image_w, image_c])
        train_label_node = tf.placeholder(tf.int64, shape=[batch_size, image_h, image_w, 1])
        phase_train = tf.placeholder(tf.bool, name='phase_train')
        global_step = tf.Variable(0, trainable=False)
        images, labels = CamVidInputs(image_filenames, label_filenames, batch_size)
        val_images, val_labels = CamVidInputs(val_image_filenames, val_label_filenames, batch_size)

        loss, eval_prediction = inference(train_data_node, train_label_node, batch_size, phase_train)

        train_op = train(loss, global_step)
        saver = tf.train.Saver(tf.global_variables())
        summary_op = tf.summary.merge_all()

        with tf.Session() as sess:
            if is_finetune:
                saver.restore(sess, finetune_ckpt)
            else:
                sess.run(tf.global_variables_initializer())

            coord = tf.train.Coordinator()
            threads = tf.train.start_queue_runners(sess=sess, coord=coord)

            # Summery placeholders
            summary_writer = tf.summary.FileWriter(train_dir, sess.graph)
            average_pl = tf.placeholder(tf.float32)
            acc_pl = tf.placeholder(tf.float32)
            iu_pl = tf.placeholder(tf.float32)
            average_summary = tf.summary.scalar("test_average_loss", average_pl)
            acc_summary = tf.summary.scalar("test_accuracy", acc_pl)
            iu_summary = tf.summary.scalar("Mean_IU", iu_pl)

            for step in range(startstep, startstep + max_steps):
                feed_dict = {
                    train_data_node: images,
                    train_label_node: labels,
                    phase_train: True
                }
                start_time = time.time()
                _, loss_value = sess.run([train_op, loss], feed_dict=feed_dict)
                duration = time.time() - start_time
                if step % 10 == 0:
                    num_examples_per_step = batch_size
                    examples_per_sec = num_examples_per_step / duration
                    sec_per_batch = float(duration)

                    format_str = ('%s: step %d, loss = %.2f (%.1f examples/sec; %.3f '
                                  'sec/batch)')
                    print(format_str % (datetime.now(), step, loss_value,
                                        examples_per_sec, sec_per_batch))

                    # eval current training batch pre-class accuracy
                    pred = sess.run(eval_prediction, feed_dict=feed_dict)
                    per_class_acc(pred, labels)

                if step % 100 == 0:
                    print("start validating.....")
                    total_val_loss = 0.0
                    hist = np.zeros((NUM_CLASSES, NUM_CLASSES))
                    for test_step in range(int(TEST_ITER)):
                        val_images_batch, val_labels_batch = sess.run([val_images, val_labels])

                        _val_loss, _val_pred = sess.run([loss, eval_prediction], feed_dict={
                            train_data_node: val_images_batch,
                            train_label_node: val_labels_batch,
                            phase_train: True
                        })
                        total_val_loss += _val_loss
                        hist += get_hist(_val_pred, val_labels_batch)
                    print("val loss: ", total_val_loss / TEST_ITER)
                    acc_total = np.diag(hist).sum() / hist.sum()
                    iu = np.diag(hist) / (hist.sum(1) + hist.sum(0) - np.diag(hist))
                    test_summary_str = sess.run(average_summary, feed_dict={average_pl: total_val_loss / TEST_ITER})
                    acc_summary_str = sess.run(acc_summary, feed_dict={acc_pl: acc_total})
                    iu_summary_str = sess.run(iu_summary, feed_dict={iu_pl: np.nanmean(iu)})
                    # print_hist_summery(hist)
                    print(" end validating.... ")

                    summary_str = sess.run(summary_op, feed_dict=feed_dict)
                    summary_writer.add_summary(summary_str, step)
                    summary_writer.add_summary(test_summary_str, step)
                    summary_writer.add_summary(acc_summary_str, step)
                    summary_writer.add_summary(iu_summary_str, step)
                # Save the model checkpoint periodically.
                if step % 1000 == 0 or (step + 1) == max_steps:
                    checkpoint_path = os.path.join(train_dir, 'model.ckpt')
                    saver.save(sess, checkpoint_path, global_step=step)

if __name__ == '__main__':
    image_filename, lebel_filename = get_filename_list("./CamVid/train.txt")
