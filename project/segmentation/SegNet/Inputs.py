# encoding: utf-8

# @author: wenxuan
# @contact: 749935253@qq.com
# @software: PyCharm
# @file: Inputs.py
# @time: 19-5-7 下午1:59

import tensorflow as tf
from tensorflow.python.framework import ops
from tensorflow.python.framework import dtypes

IMAGE_HEIGHT = 360
IMAGE_WIDTH = 480
IMAGE_DEPTH = 3

NUM_CLASSES = 11
NUM_EXAMPLES_PER_EPOCH_FOR_TRAIN = 367
NUM_EXAMPLES_PER_EPOCH_FOR_TEST = 101
NUM_EXAMPLES_PER_EPOCH_FOR_EVAL = 1


def get_filename_list(path):
    fd = open(path)
    image_filenames = []
    label_filenames = []
    for i in fd:
        i = i.strip().split(" ")
        image_filenames.append(i[0])
        label_filenames.append(i[1])
    return image_filenames, label_filenames


def CamVidInputs(image_filenames, label_filenames, batch_size):
    images = ops.convert_to_tensor(image_filenames, dtype=dtypes.string)
    labels = ops.convert_to_tensor(label_filenames, dtype=dtypes.string)
    filename_queue = tf.train.slice_input_producer([images, labels], shuffle=True)
    image, label = CamVid_reader(filename_queue)
    min_fraction_of_examples_in_queue = 0.4
    min_queue_examples = int(NUM_EXAMPLES_PER_EPOCH_FOR_TRAIN *
                             min_fraction_of_examples_in_queue)
    print('Filling queue with %d CamVid images before starting to train. '
          'This will take a few minutes.' % min_queue_examples)

    # Generate a batch of images and labels by building up a queue of examples.
    return _generate_image_and_label_batch(image, label,
                                           min_queue_examples, batch_size,
                                           shuffle=True)


def _generate_image_and_label_batch(image, label, min_queue_examples,
                                    batch_size, shuffle):
    """Construct a queued batch of images and labels.

    Args:
      image: 3-D Tensor of [height, width, 3] of type.float32.
      label: 3-D Tensor of [height, width, 1] type.int32
      min_queue_examples: int32, minimum number of samples to retain
        in the queue that provides of batches of examples.
      batch_size: Number of images per batch.
      shuffle: boolean indicating whether to use a shuffling queue.

    Returns:
      images: Images. 4D tensor of [batch_size, height, width, 3] size.
      labels: Labels. 3D tensor of [batch_size, height, width ,1] size.
    """
    # Create a queue that shuffles the examples, and then
    # read 'batch_size' images + labels from the example queue.
    num_preprocess_threads = 1
    if shuffle:
        images, label_batch = tf.train.shuffle_batch(
            [image, label],
            batch_size=batch_size,
            num_threads=num_preprocess_threads,
            capacity=min_queue_examples + 3 * batch_size,
            min_after_dequeue=min_queue_examples)
    else:
        images, label_batch = tf.train.batch(
            [image, label],
            batch_size=batch_size,
            num_threads=num_preprocess_threads,
            capacity=min_queue_examples + 3 * batch_size)

    # Display the training images in the visualizer.
    # tf.image_summary('images', images)

    return images, label_batch


def CamVid_reader(filename_queue):
    image_filename = filename_queue[0]
    label_filename = filename_queue[1]
    imageValue = tf.read_file(image_filename)
    labelValue = tf.read_file(label_filename)
    image_bytes = tf.image.decode_png(imageValue)
    label_bytes = tf.image.decode_png(labelValue)
    image = tf.reshape(image_bytes, (IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_DEPTH))
    label = tf.reshape(label_bytes, (IMAGE_HEIGHT, IMAGE_WIDTH, 1))

    return tf.cast(image, tf.float32), label
