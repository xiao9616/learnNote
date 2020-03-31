# TensorFlow Serving

## 介绍

TensorFlow Serving是一个针对机器学习模型的灵活，高性能的服务系统，专为生产环境而设计。使用TensorFlow Serving可以轻松部署新算法和实验，同时保持相同的服务器体系结构和API。TensorFlow Serving提供与TensorFlow模型的现成集成，但可以轻松扩展以服务于其他类型的模型。

### 概念

### docker启动

```
docker pull tensorflow/serving
```

```
docker run -itd --name serving -p 8500:8500 -p 8501:8501 -v /home/xwx/serving/models/:/models tensorflow/serving --model_config_file=/models/models.config
```

配置models.config

```
model_config_list:{
    config:{
      name:"saved_model_half_plus_two_cpu",
      base_path:"/models/saved_model_half_plus_two_cpu",
      model_platform:"tensorflow"
    },
    config:{
      name:"fasion_mnist",
      base_path:"/models/fasion_mnist",
      model_platform:"tensorflow"
    }
}
```

```
curl -d '{"instances": [1.0, 2.0, 5.0]}'   -X POSThttp://172.28.4.118:8501/v1/models/saved_model_half_plus_two_cpu:predict
```

