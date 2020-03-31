import base64

import general_rpc


def messageHandle(jsonStr):
    print('收到服务端普通字符串响应>>>' + jsonStr)


def streamHandle(bytes):
    print('收到服务端流响应>>> '+ str(len(bytes)))



if __name__ == '__main__':
    client = general_rpc.GeneralClient('localhost', None)
    json = '{"name":"test"}'

    # 普通的请求
    client.request(json, messageHandle)

    ## 流传输
    with open('./answer.jpg', 'rb') as fp:
        bytes = fp.read()
        print(bytes)
    client.requestStream(bytes,streamHandle)

