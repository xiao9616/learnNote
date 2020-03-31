# protoc buffer

## 定义消息类型

```
syntax="proto3"

message SearchRequest {
	string query=1;
	int32 page_number=2;
	int32 result_per_page=3;
}
```

第一行的含义是限定该文件使用的是proto3的语法，如果没有 syntax = "proto3";

SearchRequest定义有三个承载消息的属性，每一个被定义在SearchRequest消息体中的字段，都是由数据类型和属性名称组成。

每一个被定义在消息中的字段都会被分配给一个唯一的标量，这些标量用于标识你定义在二进制消息格式中的属性，标量一旦被定义就不允许在使用过程中再次被改变。

## 指定属性

singular: 一个正确的消息可以有零个或者多个这样的消息属性(但是不要超过一个).

repeated: 这个属性可以在一个正确的消息格式中重复任意次数(包括零次)

```
message Foo {
  reserved 2;
  reserved "foo", "bar";
}
```

定义保留属性为"foo", "bar"，定义保留属性位置为2，即在2这个位置上不可以定义属性，如:string name=2;是不允许的.

## 数据类型

| **.proto Type** | **Java Type** |
| --------------- | ------------- |
| float           | float         |
| double          | double        |
| int32           | int           |
| int64           | long          |
| uint32          | int           |
| uint64          | long          |
| bool            | boolean       |
| string          | String        |
| bytes           | ByteString    |

类型默认值:

`string`类型,默认值是空字符串,注意不是null

 `bytes`类型,默认值是空bytes

 `bool`类型，默认值是false

 `数字`类型,默认值是0

 `枚举`类型,默认值是第一个枚举值,即0

 `repeated`修饰的属性，默认值是空（在相对应的编程语言中通常是一个空的list）

### 枚举

```
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
  enum Corpus {
    UNIVERSAL = 0;
    WEB = 1;
    IMAGES = 2;
    LOCAL = 3;
    NEWS = 4;
    PRODUCTS = 5;
    VIDEO = 6;
  }
  Corpus corpus = 4;
}
```

Corpus枚举类型的第一个枚举值是0，每一个枚举值定义都会与一个常量映射，而这些常量的第一个常量值必须为0

```rust
enum EnumAllowingAlias {
  option allow_alias = true;
  UNKNOWN = 0;
  STARTED = 1;
  RUNNING = 1;
}
enum EnumNotAllowingAlias {
  UNKNOWN = 0;
  STARTED = 1;
  //如果解除这个注释编译器在编译该proto文的时候会报错
  // RUNNING = 1;  
}
```

定义枚举类型的第一行中添加allow_alias选项，并将值设置为true即可，如果没有设置该值就是用别名，在编译的时候会报错。

### 引用其他类型

```
message SearchResponse {
  repeated Result results = 1;
}

message Result {
  string url = 1;
  string title = 2;
  repeated string snippets = 3;
}
```

### 导入其他proto中定义

```
syntax = "proto3";
import "test/result.proto";
package test1;

message SearchResponse {
  //包名.消息名
  repeated test2.Result results = 1;
}
```

### 内嵌类型

```
message SearchResponse {
  message Result {
    string url = 1;
    string title = 2;
    repeated string snippets = 3;
  }
  repeated Result results = 1;
}
```

### map

```
map<key_type,value_type> map_field = N;
```

key_type可以是任何整数或字符串类型（除浮点类型和字节之外的任何标量类型,枚举类型也是不合法的key类型），value_type可以是任何类型的数据。

### package

```
package foo.bar;
message Open { ... }
```

```
Message Foo {
  ...
  foo.bar.Open open = 1;
  ...
}
```

## 服务

```
service SearchService {
    //  方法名  方法参数                 返回值
    rpc Search(SearchRequest) returns (SearchResponse); 
}
```

