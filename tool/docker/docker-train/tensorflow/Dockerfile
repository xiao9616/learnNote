FROM ubuntu:16.04

MAINTAINER xiao "18710760109@163.com"

RUN mkdir /app

VOLUME /app

ADD . /require

ADD sources.list /etc/apt/sources.list

WORKDIR /require

RUN apt-get update && apt-get upgrade -y && apt-get install -y python3 wget vim

RUN wget -O /tmp/get-pip.py https://bootstrap.pypa.io/get-pip.py && python3 /tmp/get-pip.py && pip install --upgrade pip

RUN pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple/

RUN pip install -U tensorflow

RUN pip install -r requirements.txt

WORKDIR /app

EXPOSE 5000 8080

CMD ["bash"]

