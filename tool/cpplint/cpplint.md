# cpplint

## 介绍

Cpplint是一个Python脚本，作为一款开源免费的代码静态检测工具，Google也使用它作为自己的C++代码检测工具，也就是说，只要你想代码遵从Google C++代码规范，那么Cpplint将会提供很好的代码静态检测支持。


- Cpplint.py支持的文件格式包括.cc、.h、.cpp、.cu、.cuh。
- Cpplint只是一个代码风格检测工具，其并不对代码逻辑、语法错误等进行检查。

## 安装

```shell
pip install cpplint
```

## 集成到Clion中使用

1.安装cpplint插件

```
Clion -> File -> Settings -> Plugins ->搜索cpplint -> install
```

2.参数设置

