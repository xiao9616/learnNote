# =============================================
# -*- coding: utf-8 -*-           
# @Time    : 2019/12/24 下午2:27    
# @Author  : xiao9616           
# @Email   : 749935253@qq.com   
# @File    : client.py         
# @Software: PyCharm
# ============================================
import threading
import grpc
import time
import base64
import os
import sys
import argpars
import upload_pb2
import upload_pb2_grpc
import numpy as np

def getfile(path,chunksize):
    readsize=0
    filesize=sys.getsizeof(path)
    data=[]
    if filesize<chunksize:
        path=bytes(path)
        data.append(base64.b64encode(path))
    return data

def run(tf_file,path,ip):
    channel=grpc.insecure_channel('{}:50053'.format(ip))
    stub=upload_pb2_grpc.UploadStub(channel)
    def strem():
        for tf in tf_file:
            yield upload_pb2.Tdata(data=tf,size=len(tf_file),name=path)
    response=stub.Fileup(strem())
    stri=response.data
    list=stri.split(" ")
    for i in range(len(list)):
        list[i]=np.fromstring(list[i],dtype=int,sep=',')
    list=np.array(list)
    return list


