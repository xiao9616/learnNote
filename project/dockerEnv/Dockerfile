FROM python:3
EXPOSE 5000 1414
WORKDIR /opt/app
COPY . /opt/app
RUN pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple/
RUN pip install -r requirements.txt
CMD python app.py