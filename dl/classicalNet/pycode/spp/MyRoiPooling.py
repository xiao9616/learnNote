from keras.layers import Layer
import keras.backend as K


class RoiPooling(Layer):
    '''
    金字塔池化
    参数：
        pool_list:池化区域，例如[1,2,4]表示1x1,2x2,4x4的最大池化输出
        num_rois:使用多少个roi
        input_shape:[x_img,x_roi]
                    如果dim_ordering="th" x_img=[1,channels,row,col]
                    如果dim_ordering="tf" x_img=[1,row,col,channels]
                    [1,num_rois,4] (x,y,w,h)
        output_shape:
                    (1, num_rois, channels * sum([i * i for i in pool_list])
    '''

    # 初始化参数
    def __init__(self, pool_list, num_rois, **kwargs):
        self.dim_ordering = K.image_dim_ordering()
        self.pool_list = pool_list
        self.num_rois = num_rois
        self.num_outputs_per_channel = sum([i * i for i in pool_list])
        super(RoiPooling, self).__init__(**kwargs)
    # build 用来定义权重
    def build(self, input_shape):
        if self.dim_ordering == 'th':
            self.nb_channel = input_shape[0][1]
        elif self.dim_ordering == 'tf':
            self.nb_channel = input_shape[0][3]

    # 计算输出shape

    def compute_output_shape(self, input_shape):
        return None, self.num_rois, self.nb_channel * self.num_outputs_per_channel

    # 配置信息

    def get_config(self):
        config = {'pool_list': self.pool_list, 'num_rois': self.num_rois}
        base_config = super(RoiPooling, self).get_config()
        return dict(list(base_config.items()) + list(config.items()))

    # 定义前向计算

    def call(self, x, mask=None):
        assert (len(x) == 2)
        img = x[0]
        rois = x[1]
        input_shape = K.shape(img)
        outputs = []

        for roi_idx in range(self.num_rois):
            x = rois[0, roi_idx, 0]
            y = rois[0, roi_idx, 1]
            w = rois[0, roi_idx, 2]
            h = rois[0, roi_idx, 3]

            row_length = [w / i for i in self.pool_list]
            col_length = [h / i for i in self.pool_list]

            if self.dim_ordering == 'th':
                for pool_index, num_pool_regions in enumerate(self.pool_list):
                    for ix in range(num_pool_regions):
                        for iy in range(num_pool_regions):
                            x1 = x + ix * col_length[pool_index]
                            x2 = x1 + col_length[pool_index]
                            y1 = y + iy * row_length[pool_index]
                            y2 = y1 + row_length[pool_index]

                            x1 = K.cast(K.round(x1), 'int32')
                            x2 = K.cast(K.round(x2), 'int32')
                            y1 = K.cast(K.round(y1), 'int32')
                            y2 = K.cast(K.round(y2), 'int32')

                            new_shape = [
                                input_shape[0], input_shape[1], y2 - y1, x2 - x1]
                            x_crop = img[:, :, y1:y2, x1:x2]
                            xm = K.reshape(x_crop, new_shape)
                            pooled_val = K.max(xm, axis=(2, 3))
                            outputs.append(pooled_val)
            elif self.dim_ordering == 'tf':
                for pool_num, num_pool_regions in enumerate(self.pool_list):
                    for ix in range(num_pool_regions):
                        for jy in range(num_pool_regions):
                            x1 = x + ix * col_length[pool_num]
                            x2 = x1 + col_length[pool_num]
                            y1 = y + jy * row_length[pool_num]
                            y2 = y1 + row_length[pool_num]

                            x1 = K.cast(K.round(x1), 'int32')
                            x2 = K.cast(K.round(x2), 'int32')
                            y1 = K.cast(K.round(y1), 'int32')
                            y2 = K.cast(K.round(y2), 'int32')

                            new_shape = [input_shape[0], y2 - y1,
                                         x2 - x1, input_shape[3]]
                            x_crop = img[:, y1:y2, x1:x2, :]
                            xm = K.reshape(x_crop, new_shape)
                            pooled_val = K.max(xm, axis=(1, 2))
                            outputs.append(pooled_val)


        final_output = K.concatenate(outputs, axis=0)
        final_output = K.reshape(
            final_output,
            (1,
             self.num_rois,
             self.nb_channel *
             self.num_outputs_per_channel))

        return final_output
