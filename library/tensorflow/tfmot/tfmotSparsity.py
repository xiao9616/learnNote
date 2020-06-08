# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2020/5/26 下午4:40    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : tfmotSparsity.py
# @Software: PyCharm
# @Discript:keras模型的减枝pruning
# ============================================
import tensorflow as tf
from tensorflow import keras
import numpy as np
import os
import tempfile
import tensorflow_model_optimization as tfmot


def base_model():
    '''
    base model
    '''
    mnist = tf.keras.datasets.mnist
    (train_images, train_labels), (test_images, test_labels) = mnist.load_data()
    train_images = train_images / 255.0
    test_images = test_images / 255.0

    model = keras.Sequential(
        [
            keras.layers.InputLayer(input_shape=(28, 28)),
            keras.layers.Reshape(target_shape=(28, 28, 1)),
            keras.layers.Conv2D(filters=12, kernel_size=(3, 3), activation=tf.nn.relu),
            keras.layers.MaxPool2D(pool_size=(2, 2)),
            keras.layers.Flatten(),
            keras.layers.Dense(10)
        ]
    )

    model.compile(optimizer="adam", loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                  metrics=['accuracy'])
    model.summary()
    model.fit(train_images, train_labels, epochs=2, validation_split=0.1)
    _, baseline_model_accuracy = model.evaluate(test_images, test_labels, verbose=1)
    print("baseline test accuracy：", baseline_model_accuracy)
    _, keras_file = tempfile.mkstemp('.h5')
    tf.keras.models.save_model(model, keras_file, include_optimizer=False)
    print('save baseline model to', keras_file)

    '''
    prune model
    '''
    prune_low_magnitude = tfmot.sparsity.keras.prune_low_magnitude
    batch_size = 128
    epochs = 2
    validation_split = 0.1
    num_images = train_images.shape[0] * (1 - validation_split)
    end_step = np.ceil(num_images / batch_size).astype(np.int32) * epochs
    prune_params = {
        "pruning_schedule": tfmot.sparsity.keras.PolynomialDecay(initial_sparsity=0.50, final_sparsity=0.80,
                                                                 begin_step=0, end_step=end_step)
    }

    model_prune = prune_low_magnitude(model, **prune_params)
    model_prune.compile(optimizer="adam", loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
                        metrics=['accuracy'])
    model_prune.summary()
    logdir = tempfile.mkdtemp()
    callbacks = [
        tfmot.sparsity.keras.UpdatePruningStep(),
        tfmot.sparsity.keras.PruningSummaries(log_dir=logdir),
    ]
    model_prune.fit(train_images, train_labels, batch_size=batch_size, epochs=epochs, validation_split=validation_split,
                    callbacks=callbacks)
    _, model_for_pruning_accuracy = model_prune.evaluate(
        test_images, test_labels, verbose=1)

    print('Baseline test accuracy:', baseline_model_accuracy)
    print('Pruned test accuracy:', model_for_pruning_accuracy)

    model_export = tfmot.sparsity.keras.strip_pruning(model_prune)
    _, pruned_keras_file = tempfile.mkstemp('.h5')
    tf.keras.models.save_model(model_export,pruned_keras_file,include_optimizer=False)
    print('Saved pruned Keras model to:', pruned_keras_file)

    '''
    tflite model
    '''
    converter=tf.lite.TFLiteConverter.from_keras_model(model_export)
    pruned_tflite_model = converter.convert()
    _, pruned_tflite_file = tempfile.mkstemp('.tflite')

    with open(pruned_tflite_file, 'wb') as f:
        f.write(pruned_tflite_model)

    print('Saved pruned TFLite model to:', pruned_tflite_file)

    '''
    quantization
    '''
    converter = tf.lite.TFLiteConverter.from_keras_model(model_export)
    converter.optimizations = [tf.lite.Optimize.DEFAULT]
    quantized_and_pruned_tflite_model = converter.convert()

    _, quantized_and_pruned_tflite_file = tempfile.mkstemp('.tflite')

    with open(quantized_and_pruned_tflite_file, 'wb') as f:
        f.write(quantized_and_pruned_tflite_model)

    print('Saved quantized and pruned TFLite model to:', quantized_and_pruned_tflite_file)

if __name__ == '__main__':
    base_model()
