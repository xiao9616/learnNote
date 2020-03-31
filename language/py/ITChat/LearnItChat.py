# encoding: utf-8

# @author: wenxuan
# @contact: 749935253@qq.com
# @software: PyCharm
# @file: LearnItChat.py
# @time: 19-6-20 上午10:05

import itchat as wx
import requests

apiUrl = 'http://www.tuling123.com/openapi/api'
data = {
    'key': 'eb720a8970964f3f855d863d24406576',  # 如果这个Tuling Key不能用，那就换一个
    'info': 'hello',  # 这是我们发出去的消息
    'userid': 'wechat-robot',  # 这里你想改什么都可以
}
# 我们通过如下命令发送一个post请求
r = requests.post(apiUrl, data=data).json()

# 让我们打印一下返回的值，看一下我们拿到了什么
print(r)


@wx.msg_register(wx.content.TEXT)
def print_content(msg):
    print(msg['Text'])
    return msg['Text']


wx.auto_login(hotReload=True)
wx.run()
