# MongoDB

## 一.介绍

MongoDB 是一个基于分布式文件存储(JSON)的数据库。由 C++ 语言编写。旨在为 WEB 应用提供可扩展的高性能数据存储解决方案。

MongoDB 是一个介于关系数据库和非关系数据库之间的产品，是非关系数据库当中功能最丰富，最像关系数据库的。

NoSQL(NoSQL = Not Only SQL )，意即"不仅仅是SQL"。

### ACID原则

1、A (Atomicity) 原子性

2、C (Consistency) 一致性

3、I (Isolation) 独立性

4、D (Durability) 持久性

### CAP定理（CAP theorem）

一致性(Consistency) (所有节点在同一时间具有相同的数据)
可用性(Availability) (保证每个请求不管成功或者失败都有响应)
分隔容忍(Partition tolerance) (系统中任意信息的丢失或失败不会影响系统的继续运作)

CA - 单点集群，满足一致性，可用性的系统，通常在可扩展性上不太强大。
CP - 满足一致性，分区容忍性的系统，通常性能不是特别高。
AP - 满足可用性，分区容忍性的系统，通常可能对一致性要求低一些。

## 二.安装

### docker安装

```
docker pull mongo
docker run -p 27017:27017 -v $PWD/db:/data/db -d --name mymongo mongo
```

## 三.使用

### 创建/删除数据库

show dbs

db

use local

db.dropDatabase()

### 创建/删除集合

show tables

db.createCollection("runoob")

db.runoob.insert({"name":"xiao"})

db.runoob.drop()

### 插入/删除文档

db.runoob.find()

db.runoob.insert({"name":"wenxuan","age":27})

db.runoob.remove({"age":27})

db.runoob.remove({"age":27},1)

db.runoob.remove({})

### 更新文档

db.runoob.update({"age":27},{$set:{"age":18}},{multi:true})

db.runoob.save({"_id":})

### 查询文档

db.runoob.find()

db.runoob.find().pretty() //美化输出

db.runoob.find().limit(100) //限制输出100条

db.runoob.find().limit(100).skip(1) //显示2到101条

db.runoob.find().sort({"age":1}) //1 为升序排列，而 -1 是用于降序排列。

### 条件

(>) 大于 - $gt
(<) 小于 - $lt
(>=) 大于等于 - $gte
(<= ) 小于等于 - $lte

(!=) 不等于 - $ne
(= ) 等于 - $eq



按照条件查找

db.runoob.find({"age":{$gt:18,$lt:60}})

按照类型type查找 $type

db.runoob.find({"age":{$type:"string"}})

### 索引

索引通常能够极大的提高查询的效率，如果没有索引，MongoDB在读取数据时必须扫描集合中的每个文件并选取那些符合查询条件的记录。这种扫描全集合的查询效率是非常低的，特别在处理大量的数据时，查询可以要花费几十秒甚至几分钟，这对网站的性能是非常致命的。索引是特殊的数据结构，索引存储在一个易于遍历读取的数据集合中，索引是对数据库表中一列或多列的值进行排序的一种结构

db.runoob.createIndex({"age":1,"name":-1})

### 聚合

聚合(aggregate)主要用于处理数据(诸如统计平均值,求和等)，并返回计算后的数据结果。

db.runoob.aggregate([{$group:{_id:"$by_user",num:{$sum:1}}}])

### 复制

MongoDB复制是将数据同步在多个服务器的过程。复制提供了数据的冗余备份，并在多个服务器上存储数据副本，提高了数据的可用性， 并可以保证数据的安全性。复制还允许您从硬件故障和服务中断中恢复数据。mongodb的复制至少需要两个节点。其中一个是主节点，负责处理客户端请求，其余的都是从节点，负责复制主节点上的数据。mongodb各个节点常见的搭配方式为：一主一从、一主多从。

在Mongo客户端使用命令rs.initiate()来启动一个新的副本集。我们可以使用rs.conf()来查看副本集的配置.查看副本集状态使用 rs.status() 命令

```
mongod --port 27017 --dbpath "D:\set up\mongodb\data" --replSet rs0
```

副本集添加成员

```
rs.add("rs0:27017")
```

判断当前运行的Mongo服务是否为主节点

```
db.isMaster()
```

主从在主机宕机后所有服务将停止，而副本集在主机宕机后，副本会接管主节点成为主节点，不会出现宕机的情况。

### 分片

当MongoDB存储海量的数据时，一台机器可能不足以存储数据，也可能不足以提供可接受的读写吞吐量。这时，我们就可以通过在多台机器上分割数据，使得数据库系统能存储和处理更多的数据。

