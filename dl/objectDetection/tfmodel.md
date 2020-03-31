# tensorflow [model](https://github.com/tensorflow/models)

## 一.安装

下载

```
git clone https://github.com/tensorflow/models
```

cd 到 research

```
python setup.py install
```

在research中执行

```
protoc object_detection/protos/*.proto --python_out=.
```

添加环境变量

```
export PYTHONPATH=$PYTHONPATH:`pwd`:`pwd`/slim
```

重启终端

测试

```
python object_detection/builders/model_builder_test.py
```

```
Ran 16 tests in 0.096s
OK (skipped=1)
```

