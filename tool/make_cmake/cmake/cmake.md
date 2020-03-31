# cmake

```
cmake_minimum_required (VERSION 2.8)	//指定运行此配置文件所需的 CMake 的最低版本

project (appName)	//设置项目名称

add_executable (appName main.cc)	//将源文件main编译为appName的可执行文件

aux_source_directory(. DIR_SRC)		//查找当前目录下所有源文件，并添加到DIR_SRC变量中
add_executable (appName ${DIR_SRC})

add_subdirectory (sub)		//添加sub子目录

add_library (func ${DIR_SRC})		//生成链接库func

target_link_libraries (appName func)		//添加链接库func到appName

find_package (OpenCV 4.0 REQUIRED)
```

