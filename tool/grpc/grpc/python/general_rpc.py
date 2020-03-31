import time
import logging
from concurrent import futures

import grpc
import general_pb2_grpc, general_pb2

"""
General RPC Client 对象 
构造传入host地址。默认端口50050
"""
LOG_FORMAT = "%(asctime)s - %(levelname)s - %(message)s"  # 日志格式化输出
DATE_FORMAT = "%m/%d/%Y %H:%M:%S %p"  # 日期格式
logging.basicConfig(level=logging.INFO, format=LOG_FORMAT, datefmt=DATE_FORMAT)  # 调用

size = 1024 * 1024


class GeneralClient:
    host = 'localhost'
    port = '50050'
    channel = None
    stub = None

    def __init__(self, host, port):
        self.host = host
        if not port is None:
            self.port = port
        self.channel = grpc.insecure_channel(host + ':' + self.port)
        self.stub = general_pb2_grpc.GeneralStub(self.channel)

    ## 简单json字符串参数请求
    def request(self, jsonStr, handle):
        ## jsonStr
        request = general_pb2.Request(jsonStr=jsonStr)
        reply = self.stub.messageHandle(request)
        handle(reply.jsonStr)

    ##stream 请求
    ## bytes 传字节数组参数.
    ##handle 函数传入服务端返回字节数组
    def requestStream(self, bytes, handle):
        for reply_stream in self.stub.messageStreamHandle(generate_request(bytes)):
            if reply_stream.jsonStr == '1':
                handle(reply_stream.byteStream)

    ## 生产stream request 对象


## 生成rpc 流请求参数
def generate_request(bytes):
    if (len(bytes) <= size):
        yield general_pb2.Request(byteStream=bytes)
    else:
        ##切分1M 发送一次
        for i in range(0, len(bytes), size):
            yield general_pb2.Request(byteStream=bytes[i:i + size])


## 生成rpc 流返回数据
def generate_reply(bytes):
    if (len(bytes) <= size):
        yield general_pb2.Reply(byteStream=bytes)
    else:
        ##切分1M 发送一次
        for i in range(0, len(bytes), size):
            yield general_pb2.Reply(byteStream=bytes[i:i + size])


"""
 general service 实现

"""


class GeneralService(general_pb2_grpc.GeneralServicer):
    port = '50050'
    server = None
    handle = None
    streamCompleted = None

    def __init__(self, port):
        self.port = port
        self.server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
        self.server.add_insecure_port('[::]:' + self.port)

    ##简单的一次请求，一次应答
    def messageHandle(self, request, context):
        if self.handle is None:
            raise RuntimeError('message Handle is None')
        result = self.handle(request.jsonStr, False)
        return general_pb2.Reply(jsonStr=result)

    ## 流传输
    def messageStreamHandle(self, request_iterator, context):
        for request in request_iterator:
            ## 每次流处理完的返回流
            if not self.handle is None:
                bytes0 = self.handle(request.byteStream, True)
                if not bytes0 is None:
                    return generate_reply(bytes0)
        # ## 流传输完成返回
        if not self.streamCompleted is None:
            bytes = self.streamCompleted()
            if not bytes is None:
                return generate_reply(bytes)


"""
 启动一个gpr 服务
"""


def startService(port, handle, streamCompleted):
    if port is None:
        port = '50050'
    generalService = GeneralService(port)
    generalService.handle = handle
    generalService.streamCompleted = streamCompleted
    general_pb2_grpc.add_GeneralServicer_to_server(generalService, generalService.server)
    generalService.server.start()
    logging.info('rpc server started,' + generalService.port)
    try:
        while True:
            time.sleep(60 * 60 * 24)  # one day in seconds
    except KeyboardInterrupt:
        generalService.server.stop(0)
