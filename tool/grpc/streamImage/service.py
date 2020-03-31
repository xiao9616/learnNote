# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2019/12/24 下午2:31    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : service.py         
# @Software: PyCharm
# ============================================
import re
import threading

import cv2
import grpc
import time
import base64
import os
import sys
import argpars
import upload_pb2
import upload_pb2_grpc
import numpy as np

class Upload(upload_pb2_grpc.UploadServicer):
    def Fileup(self, request_iterator, context):
        i=0
        file_exist=False
        while 1:
            for Tdata in request_iterator:
                out_ite=Tdata
                print(type(out_ite))
                binary_data=base64.b64decode(out_ite.data)
                if(os.path.exists(out_ite.name) and i==0) or file_exist:
                    if i==0:
                        print('{} already exists,So no copy this file.'.format(out_ite.name))
                        file_exist=True
                        pass
                else:
                    if re.search('/', out_ite.name):
                        os.makedirs(os.path.dirname(out_ite.name), exist_ok=True)
                        file_name = out_ite.name
                    else:
                        file_name = out_ite.nam
                    image=np.fromstring(binary_data,np.uint8).reshape(480,640,3)
                    image=cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
                    cv2.imwrite(file_name,image)
                i+=1

                list1 = [[100, 200, 300, 400], [12, 120, 133, 140]]
                list1 = np.array(list1)
                stri = ""
                # 将数组转换成字符串
                for i in range(len(list1)):
                    for j in range(len(list1[i])):
                        stri += "".join(str(list1[i][j]))
                        if (j < (len(list1[i]) - 1)):
                            stri += ","
                    if (i < (len(list1) - 1)):
                        stri += " "
                return upload_pb2.Tdata(data=stri, size=out_ite.size, name=out_ite.name)



