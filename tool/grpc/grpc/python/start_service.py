import general_rpc

##报存客户端每次传入的流
bytearray = []
##回调处理函数
def messageHandle(obj, stream):
    print(type(obj))
    if (stream):
        print("收到客户端一次流请求，根据业务需要进行处理")
        ##存入数组
        bytearray.append(obj)
        ##这里接收所有图片字节不返回对象，
        # 其他业务如果每次传输流过来有需要单独处理可以在这里返回本次处理结果
        return None
    else:
        print('收到客户普通json请求,进行业务处理，' + obj)
        str = '{"result":"我是算法计算结果"}'
        return str


def streamCompleted():
    print('流传输完成业务处理.......')
    ##图片传输完成，进行图片算法处理
    with open("./img.jpg","wb") as f:
        for b in bytearray:
            f.write(b)

    ##流式返回
    with open("./img.jpg", 'rb') as fp:
        bytes = fp.read()

    return None


if __name__ == '__main__':
    ##启动一个rpc 服务端
    general_rpc.startService(None, messageHandle, streamCompleted)
