#coding = utf-8
'''
Author:xiao
date= 上午10:10
'''

import cv2 as cv
from skimage import segmentation
from time import time
import torch
import torch.nn as nn
import torch.nn.functional as f
import torch.optim as optim
from torch.autograd import Variable
import numpy as np
import argparse
import os

parser = argparse.ArgumentParser(description='unsupervised segmentation')
parser.add_argument(
    '--nChannel',
    metavar='N',
    default=100,
    type=int,
    help='number of channels')
parser.add_argument(
    '--maxIter',
    metavar='T',
    default=128,
    type=int,
    help='number of maximum iterations')
parser.add_argument(
    '--minLabels',
    metavar='minL',
    default=3,
    type=int,
    help='minimum number of labels')
parser.add_argument(
    '--lr',
    metavar='LR',
    default=0.1,
    type=float,
    help='learning rate')
parser.add_argument(
    '--nConv',
    metavar='M',
    default=2,
    type=int,
    help='number of converlution layers')
parser.add_argument(
    '--num_superpixels',
    metavar='K',
    default=10000,
    type=int,
    help='number of superpixels')
parser.add_argument(
    '--compactness',
    metavar='C',
    default=100,
    type=float,
    help='compactness of superpixels')
parser.add_argument(
    '--visualize',
    metavar='1 or 0',
    default=1,
    type=int,
    help='visualize flag')
parser.add_argument(
    '--input',
    metavar='filename',
    default='image/woof.jpg',
    type=str,
    help='input filename')
args = parser.parse_args()


class MyNet(nn.Module):
    def __init__(self, input_dim):
        self.conv1 = nn.Conv2d(
            input_dim,
            args.nChannel,
            kernel_size=3,
            stride=1,
            padding=1)
        self.bn1 = nn.BatchNorm2d(args.nChannel)
        self.conv2 = []
        self.bn2 = []
        for i in range(args.nConv - 1):
            self.conv2.append(
                nn.Conv2d(
                    args.nChannel,
                    args.nChannel,
                    kernel_size=3,
                    stride=1,
                    padding=1
                )
            )
            self.bn2.append(nn.BatchNorm2d(args.nChannel))
        self.conv3 = nn.Conv2d(
            args.nChannel,
            args.nChannel,
            kernel_size=1,
            stride=1,
            padding=0)
        self.bn3 = nn.BatchNorm2d(args.nChannel)

    def forward(self, x):
        x = self.conv1(x)
        x = f.relu(x)
        x = self.bn1(x)
        for i in range(args.nConv - 1):
            x = self.conv2[i](x)
            x = self.bn2[i](x)
        x = self.conv3(x)
        x = self.bn3(x)
        return x


def run():
    start_time = time()
    img = cv.imread(args.input)
    seg_map = segmentation.felzenszwalb(
        img, scale=32, sigma=0.5, min_size=64).flatten()
    seg_lab = [np.where(seg_map == u_labels)[0]
               for u_labels in np.unique(seg_map)]
    device = torch.device('cpu')
    tensor = img.transpose((2, 0, 1))
    tensor = tensor.astype(np.float32) / 255.0
    tensor = tensor[np.newaxis, :, :, :]
    tensor = torch.from_numpy(tensor)

    model = MyNet(input_dim=3)
    loss_fn = torch.nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=5e-2, momentum=0.9)
    image_flatten = img.reshape((-1, 3))
    color_avg = np.random.randint(255, size=(100, 3))
    image_show = img
    start_time = time()
    model.train()
    for batch_idx in range(args.maxIter):
        optimizer.zero_grad()
        output = model(tensor)[0]
        output = output.permute(1, 2, 0).view(-1, args.nChannel)
        target = torch.argmax(output, 1)
        im_target = target.data.cpu().numpy()
        for inds in seg_lab:
            u_labels, hist = np.unique(im_target[inds], return_counts=True)
            im_target[inds] = u_labels[np.argmax(hist)]

        target = torch.from_numpy(im_target)
        target = target.to(device)
        loss = criterion(output, target)
        loss.backward()
        optimizer.step()

        un_label, lab_inverse = np.unique(im_target, return_inverse=True, )
        if un_label.shape[0] < args.max_label_num:  # update show
            img_flatten = image_flatten.copy()
            if len(color_avg) != un_label.shape[0]:
                color_avg = [np.mean(
                    img_flatten[im_target == label], axis=0, dtype=np.int) for label in un_label]
            for lab_id, color in enumerate(color_avg):
                img_flatten[lab_inverse == lab_id] = color
            show = img_flatten.reshape(image.shape)
        cv2.imshow("seg_pt", show)
        cv2.waitKey(1)

        print('Loss:', batch_idx, loss.item())
        if len(un_label) < args.min_label_num:
            break
    time0 = time.time() - start_time0
    time1 = time.time() - start_time1
    print('PyTorchInit: %.2f\nTimeUsed: %.2f' % (time0, time1))
    cv.imwrite("seg_%s_%ds.jpg" % (args.input_image_path[6:-4], time1), show)


if __name__ == '__main__':
    run()
