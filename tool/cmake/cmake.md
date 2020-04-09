## Cmake

## 基础知识

### 1.windows下obj,lib,dll,exe的关系

lib是和dll对应的。lib是静态链接库的库文件，dll是动态链接库的库文件。 
所谓静态就是link的时候把里面需要的东西抽取出来安排到你的exe文件中，以后运行你的exe的时候不再需要lib。
所谓动态就是exe运行的时候依赖于dll里面提供的功能，没有这个dll，你的exe无法运行。

源代码和最终目标文件中过渡的就是中间代码obj，实际上之所以需要中间代码，是你不可能一次得到目标文件。比如说一个exe需要很多的cpp文件生成。而编译器一次只能编译一个cpp文件。这样编译器编译好一个cpp以后会将其编译成obj，当所有必须要的cpp都编译成obj以后，再统一link成所需要的exe，应该说缺少任意一个obj都会导致exe的链接失败。obj里存的是编译后的代码跟数据，并且有名称，所以在连接时有时会出现未解决的外部符号的问题。当连成exe后便不存在名称的概念了，只有地址。lib就是一堆obj的组合。

如果有dll文件，那么对应的lib文件一般是一些索引信息，具体的实现在dll文件中。如果只有lib文件，那么这个lib文件是静态编译出来的，索引和实现都在其中。 静态编译的lib文件有好处：给用户安装时就不需要再挂动态库了。但也有缺点，就是导致应用程序比较大，而且失去了动态库的灵活性，在版本升级时，同时要发布新的应用程序才行。

流程如下:

源代码(C/C++)->编译(obj)->链接(lib , dll)->执行文件(exe )

### 2.linux .o,.a,.so的关系

.o,是目标文件,相当于windows中的.obj文件 

.so 为共享库,是shared object,用于动态连接的,相当于windows下的dll 

.a为静态库,是好多个.o合在一起,用于静态连接 

无论静态库，还是动态库，都是由.o文件创建的。因此，我们必须将源程序.c通过gcc先编译成.o文件。当静态库和动态库同名时，gcc命令将优先使用动态库，默认去连/usr/lib和/lib等目录中的动态库，将.so复制到目录/usr/lib中即可。

一般规定函数库文件都放在/lib目录下，而且建议命令、可执行程序都放在/bin目录下

LIBRARY_PATH环境变量：指定程序静态链接库文件.a搜索路径
LD_LIBRARY_PATH环境变量：指定程序动态链接库文件.so搜索路径

运行**ldd**来看某个程序使用的共享函数库(例如ldd /bin/ls),查看.so文件使用**nm**命令

流程如下:

源代码(C/C++)->编译(o)->链接(.a , .so)->执行文件(bin)



## 介绍

**CMake**是个一个开源的跨平台自动化建构系统，用来管理软件建置的程序，并不相依于某特定编译器。它首先允许开发者编写一种平台无关的CMakeList.txt 文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化 Makefile 或工程文件，如 Unix的 Makefile 或 Windows 的 Visual Studio 工程。



## CMakeLists.txt编写

**CMakeLists.txt 的语法比较简单，由命令、注释和空格组成，其中命令是不区分大小写的。**

------

### set

设置变量的值

```cmake
#设置C++标准为11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD REQUIRED True)

#设置OpenCVConfig.cmake的位置(里面包含了所有include和lib路径)
set(OpenCV_DIR /opt/intel/openvino/opencv/cmake)

#设置库文件的生成位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
```

### message

```cmake
#打印OpenCV_DIR的值
message("${OpenCV_DIR}")
```

### cmake_minimum_required

```cmake
#设置cmake最低版本为3.14
cmake_minimum_required(VERSION 3.14)
```

### project

```cmake
#工程名字test,版本1.0
project(test VERSION 1.0)
```

### include_directories

```
#指定include路径,在add_executable之前
include_directories(" ")
```

### link_directories

```
#相当于环境变量中增加LD_LIBRARY_PATH的路径的作用s
link_directories(directory1 directory2 ...)
```

### link_libraries

```
#添加需要链接的库文件路径LINK_LIBRARIES
link_libraries(library1 <debug | optimized> library2 ...)
```

### add_executable

将目标cpp h文件生成可执行文件

```cmake
#从main.cpp person.cpp生成test可执行文件
add_executable(test main.cpp util/person.cpp util/person.h)
```

### add_library

```cmake
#将文件编译成库,会生成libmath.a文件静态库 SHARED为动态库
add_library(math STATIC mymath.cpp)
```

### add_subdirectory

```cmake
#添加子目录的路径
add_subdirectory(util)
```

### aux_source_directory

```cmake
#查找当前目录所有文件,并保存到list中
aux_source_directory(. list)
```

### target_link_libraries

```cmake
#链接库
target_link_libraries(test math)
```

### target_include_directories

```cmake
#包含链接库的头文件
target_include_directories(test 
							"${PROJECT_BINARY_DIR}"
  							"${PROJECT_SOURCE_DIR}/util")
```

### option

```cmake
#默认use_math为开
option(
	use_math
	"if or not use libmath"
	ON
)
```

## 常用变量

| 变量名               | 解释                 |
| -------------------- | -------------------- |
| CMAKE_INSTALL_PREFIX | 构建install路径      |
| $ENV{HOME}           | home环境下的目录路径 |
| PROJECT_NAME         | 工程名               |
| <PKG>_INCLUDE_DIR    | 导入包的头文件       |
| <PKG>_LIBRARIES      | 导入库的路径         |
| PROJECT_SOURCE_DIR   | 构建工程路径         |
| CMAKE_SOURCE_DIR     | 源码树顶层路径       |
| LIBRARY_OUTPUT_PATH  | lib的输出目录        |

## demo

### opencv

```cmake

```

### 生成库文件

```cmake
#设置库文件的输出位置
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

#将文件编译成库,会生成libmath.a文件静态库 SHARED为动态库，生成的库文件为lib<PKG>.a或lib<PKG>..so
add_library(math STATIC person.cpp)
```

## 库文件的生成和使用

### 1.install方式生成和安装

```
#设置安装路径 默认/usr/local
set(CMAKE_INSTALL_PREFIX /home/usr/lib)

#DESTINATION后面的路径可以自行制定，根目录默认为CMAKE_INSTALL_PREFIX,可以试用set方法进行指定
install(TARGETS MyLib
        EXPORT MyLibTargets 
        LIBRARY DESTINATION lib  # 动态库安装路径
        ARCHIVE DESTINATION lib  # 静态库安装路径
        RUNTIME DESTINATION bin  # 可执行文件安装路径
        PUBLIC_HEADER DESTINATION include  # 头文件安装路径
)

#生成并安装config.cmake
install(EXPORT opencv 
		NAMESPACE opecv：：
		FILE opencv-cnofig.cmake
		DESTINATION /lib/cmake/
)
```

https://zhuanlan.zhihu.com/p/102955723

**.cmake**文件来声明，两种模式（模块模式 配置模式）

### 2.库文件的加载

#### 模块模式

加载FindXXX.cmake

```cmak
#以opencv为例
find_path(OpenCv_INCLUDE_DIRS
		  NAMES OPENCV.H
		  PATHS "/usr/local/include"
)

find_library(OpenCV_LIBS
			NAMES OpenCV_LIBS
			PATHS "/usr/local/lib"
)

IF(OpenCv_INCLUDE_DIRS AND OpenCV_LIBS)
	SET(OpenCV_FOUND TRUE)
ENDIF(OpenCv_INCLUDE_DIRS AND OpenCV_LIBS)
```

#### 配置模式

当需要为你的项目导入其他的库时，可以使用find的方式。cmake不提供库的搜索，需要通过FindXXX.cmake或者XXXConfig.cmake的方式找到库文件的目录。

| cmake文件中的变量                      | 引用的命令                            |
| -------------------------------------- | ------------------------------------- |
| <NAME>_FOUND                           | if（<NAME>_FOUND）找到库文件          |
| <NAME>_INCLUDE_DIR     <NAME>_INCLUDES | find_path(<NAME>_INCLUDES) 库的头文件 |
| <NAME>_LIBRARY     <NAME>_LIBS         | find_library(<NAME>_LIBS) 库文件路径  |

例如OpenCV的变量

```
${OpenCV_INCLUDE_DIRS}
${OpenCV_LIBS}
```

```
find_package(OpenCV 4.2 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_subdirectory(util)
add_executable(unsigined main.cpp)
target_link_libraries(unsigined  ${OpenCV_LIBS})
```

### 3.绝对路径方式

```
#设置路径
set(lib_path /home/usr/lib)

#包含库文件的头
include_directories(${lib_path}/include)

#执行文件
add_executable(${PROJECT_NAME} main.cpp)

#链接库文件
target_link_libraries(${PROJECT_NAME} ${lib_path}/lib/libmath.so)
```

## catkin工具

使用上述的方式自定义库，比较麻烦

### 安装

```shell
sudo apt-get install python-catkin-pkg python-catkin-tools
```



## demo

#### quickstart

```cmake
find_package(OpenCV 4.2 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
link_directories()
target_link_libraries(unsigined  ${OpenCV_LIBS})
```

#### opencv

```cmake
cmake_minimum_required(VERSION 3.14)
project(unsigined)

set(CMAKE_CXX_STANDARD 14)
set(OpenCV_DIR /opt/intel/openvino/opencv/cmake)

find_package(OpenCV 4.2 REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable(unsigined main.cpp)
target_link_libraries(unsigined  ${OpenCV_LIBS})
```

