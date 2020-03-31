# encoding: utf-8

# @author: wenxuan
# @contact: 749935253@qq.com
# @software: PyCharm
# @file: main.py
# @time: 19-5-6 下午2:57

import tensorflow as tf
import model


# 第一个是参数名称，第二个参数是默认值，第三个是参数描述
flags = tf.flags
flags.DEFINE_string('testing', '', """checkpoint file""")
flags.DEFINE_string('finetune', '', """finetune checkpoint file""")
flags.DEFINE_string('log_dir', './logs', """dir to store checkpoint file""")
flags.DEFINE_string('image_dir', './CamVid/train.txt', """dir to CamVid image""")
flags.DEFINE_string('test_dir', './CamVid/test.txt', """dir to test image""")
flags.DEFINE_string('val_dir', './CamVid/val.txt', """dir to val image""")
flags.DEFINE_integer('batch_size', '5', """batch_size""")
flags.DEFINE_integer('max_steps', '20000', """max_steps""")
flags.DEFINE_integer('image_h', '360', """image height""")
flags.DEFINE_integer('image_w', '480', """image width""")
flags.DEFINE_integer('image_c', '3', """image channel""")
flags.DEFINE_integer('num_class', '11', """total class number""")
flags.DEFINE_float('learning_rate', '1e-3', """init learning rate""")
flags.DEFINE_boolean('save_image', True, """whether to save predicted image""")

FLAGS = flags.FLAGS


# 检查参数，确定是训练还是fintune还是测试
def checkArgs():
    if FLAGS.testing != '':
        print('The model is set to Testing')
        print("check point file: %s" % FLAGS.testing)
        print("CamVid testing dir: %s" % FLAGS.test_dir)
    elif FLAGS.finetune != '':
        print('The model is set to Finetune from ckpt')
        print("check point file: %s" % FLAGS.finetune)
        print("CamVid Image dir: %s" % FLAGS.image_dir)
        print("CamVid Val dir: %s" % FLAGS.val_dir)
    else:
        print('The model is set to Training')
        print("Max training Iteration: %d" % FLAGS.max_steps)
        print("Initial lr: %f" % FLAGS.learning_rate)
        print("CamVid Image dir: %s" % FLAGS.image_dir)
        print("CamVid Val dir: %s" % FLAGS.val_dir)

    print("Batch Size: %d" % FLAGS.batch_size)
    print("Log dir: %s" % FLAGS.log_dir)


# tf.app.run()的默认入口
def main(args):
    checkArgs()
    if FLAGS.testing:
        model.test(FLAGS)
    elif FLAGS.finetune:
        model.training(FLAGS, is_finetune=True)
    else:
        model.training(FLAGS, is_finetune=False)

if __name__ == '__main__':
    tf.app.run()

