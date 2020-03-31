# redis

## 安装

```docke
docker pull redis
docker run -d --name redis -p 6379:6379 redis --requirepass "xiao9616"
docker exec -it redis redis-cli -a 密码
```

内存策略

```
127.0.0.1:6379> set name 12
OK
127.0.0.1:6379> get name
"12"
127.0.0.1:6379> ttl name
(integer) -1   #该key永久有效
127.0.0.1:6379> expire name 15 #设定超时时间为15s
(integer) 1		 # 该key在内存中保留15秒
127.0.0.1:6379> ttl name
(integer) -2	 #该key不存在

volatile-lru:设定超时时间的数据中,删除最不常用的数据
allkeys-lru:查询所有key中最近不长使用的数据进行删除
```

## 命令

### 基础命令

```
auth 验证密码
ping 查看服务是否运行
quit 关闭当前链接
select 选择指定数据库
info 查看数据库统计消息
```

| 序号 | 命令及描述                                                   |
| :--- | :----------------------------------------------------------- |
| 1    | [BGREWRITEAOF](https://www.runoob.com/redis/server-bgrewriteaof.html) 异步执行一个 AOF（AppendOnly File） 文件重写操作 |
| 2    | [BGSAVE](https://www.runoob.com/redis/server-bgsave.html) 在后台异步保存当前数据库的数据到磁盘 |
| 3    | [CLIENT KILL [ip:port\] [ID client-id]](https://www.runoob.com/redis/server-client-kill.html) 关闭客户端连接 |
| 4    | [CLIENT LIST](https://www.runoob.com/redis/server-client-list.html) 获取连接到服务器的客户端连接列表 |
| 5    | [CLIENT GETNAME](https://www.runoob.com/redis/server-client-getname.html) 获取连接的名称 |
| 6    | [CLIENT PAUSE timeout](https://www.runoob.com/redis/server-client-pause.html) 在指定时间内终止运行来自客户端的命令 |
| 7    | [CLIENT SETNAME connection-name](https://www.runoob.com/redis/server-client-setname.html) 设置当前连接的名称 |
| 8    | [CLUSTER SLOTS](https://www.runoob.com/redis/server-cluster-slots.html) 获取集群节点的映射数组 |
| 9    | [COMMAND](https://www.runoob.com/redis/server-command.html) 获取 Redis 命令详情数组 |
| 10   | [COMMAND COUNT](https://www.runoob.com/redis/server-command-count.html) 获取 Redis 命令总数 |
| 11   | [COMMAND GETKEYS](https://www.runoob.com/redis/server-command-getkeys.html) 获取给定命令的所有键 |
| 12   | [TIME](https://www.runoob.com/redis/server-time.html) 返回当前服务器时间 |
| 13   | [COMMAND INFO command-name [command-name ...\]](https://www.runoob.com/redis/server-command-info.html) 获取指定 Redis 命令描述的数组 |
| 14   | [CONFIG GET parameter](https://www.runoob.com/redis/server-config-get.html) 获取指定配置参数的值 |
| 15   | [CONFIG REWRITE](https://www.runoob.com/redis/server-config-rewrite.html) 对启动 Redis 服务器时所指定的 redis.conf 配置文件进行改写 |
| 16   | [CONFIG SET parameter value](https://www.runoob.com/redis/server-config-set.html) 修改 redis 配置参数，无需重启 |
| 17   | [CONFIG RESETSTAT](https://www.runoob.com/redis/server-config-resetstat.html) 重置 INFO 命令中的某些统计数据 |
| 18   | [DBSIZE](https://www.runoob.com/redis/server-dbsize.html) 返回当前数据库的 key 的数量 |
| 19   | [DEBUG OBJECT key](https://www.runoob.com/redis/server-debug-object.html) 获取 key 的调试信息 |
| 20   | [DEBUG SEGFAULT](https://www.runoob.com/redis/server-debug-segfault.html) 让 Redis 服务崩溃 |
| 21   | [FLUSHALL](https://www.runoob.com/redis/server-flushall.html) 删除所有数据库的所有key |
| 22   | [FLUSHDB](https://www.runoob.com/redis/server-flushdb.html) 删除当前数据库的所有key |
| 23   | [INFO [section\]](https://www.runoob.com/redis/server-info.html) 获取 Redis 服务器的各种信息和统计数值 |
| 24   | [LASTSAVE](https://www.runoob.com/redis/server-lastsave.html) 返回最近一次 Redis 成功将数据保存到磁盘上的时间，以 UNIX 时间戳格式表示 |
| 25   | [MONITOR](https://www.runoob.com/redis/server-monitor.html) 实时打印出 Redis 服务器接收到的命令，调试用 |
| 26   | [ROLE](https://www.runoob.com/redis/server-role.html) 返回主从实例所属的角色 |
| 27   | [SAVE](https://www.runoob.com/redis/server-save.html) 同步保存数据到硬盘 |
| 28   | [SHUTDOWN [NOSAVE\] [SAVE]](https://www.runoob.com/redis/server-shutdown.html) 异步保存数据到硬盘，并关闭服务器 |
| 29   | [SLAVEOF host port](https://www.runoob.com/redis/server-slaveof.html) 将当前服务器转变为指定服务器的从属服务器(slave server) |
| 30   | [SLOWLOG subcommand [argument\]](https://www.runoob.com/redis/server-showlog.html) 管理 redis 的慢日志 |
| 31   | [SYNC](https://www.runoob.com/redis/server-sync.html) 用于复制功能(replication)的内部命令 |

### 高级命令

#### 事务

Redis 事务可以一次执行多个命令， 并且带有以下三个重要的保证：

- 批量操作在发送 EXEC 命令前被放入队列缓存。
- 收到 EXEC 命令后进入事务执行，事务中任意命令执行失败，其余的命令依然被执行。
- 在事务执行过程，其他客户端提交的命令请求不会插入到事务执行命令序列中。

单个 Redis 命令的执行是原子性的，但 Redis 没有在事务上增加任何维持原子性的机制，所以 Redis 事务的执行并不是原子性的。

事务可以理解为一个打包的批量执行脚本，但批量指令并非原子化的操作，中间某条指令的失败不会导致前面已做指令的回滚，也不会造成后续的指令不做。

**MULTI** 开始一个事务， 然后将多个命令入队到事务中， 最后由 **EXEC** 命令触发事务

```
multi 标记一个事务块的开始
exec 执行所有事务块内的命令
discard 取消事务，放弃事务块内的所有命令
watch 命令用于监视一个(或多个) key ，如果在事务执行之前这个(或这些)key被其他命令所改动，那么事务将被打断（回滚）
unwatch 取消watch命令对所有key的监视
```

#### 安全

```
save 将在 redis 安装目录中创建dump.rdb文件
bgsave 后台备份文件
config get dir 获取 redis 目录
```

## 数据类型

Redis支持五种数据类型：string（字符串），hash（哈希），list（列表），set（集合）及zset(sorted set)。

### String

```redis
#set get mset mget getrange getset(设定新值，返回旧值) setnx
set name xiao
get name
mset name xiao age 25
mget name age
getrange name 0 12
getset name xuan
setnx name xiao
msetnx name xiao age 26

#strlen 
strlen name

#incr decr incrby decrby incrbyfloat
incrby age 1

#append如果 key 已经存在并且是一个字符串，将指定的 value 追加到原来值的末尾
append name s
```

### Hash

hash 是一个 string 类型的 field 和 value 的映射表，hash 特别适合用于存储对象，可以存储 2的32 - 1 键值对（40多亿）

```redis
#hset hmset hget hmget hgetall 
hset user:1 id 1
hmset user:1 name xiao age 26
hget user:1 name
hmget user:1 name age
hgetall user:1

#hkeys获取全部hashset的key   hvals
hkeys user：1
hvals user：1

#hlen获取hashset的长度
hlen user：1

#hdel 删除set的key
hdel user:1 id age name

#hexists 判断字段是否存在
hexists user:1 age

#hincrby hincrbyfloat 增加
hincrby user:1 age 1

#hsetnx 只有当键不存在的时候才会设置，用于同步锁
hsetnx user:1 tall 1.7
```

### List

```
#lpush（将一个或多个值插入到列表头部） 
lpop（移出并获取列表的第一个元素） 
lpushx（将一个值插入到已存在的列表头部）
lrange（获取列表指定范围内的元素）
rpop
rpush
rpushx

lpush name xiao
lpop name
lrange name 0 12

#lrem （移除列表元素）
ltrim（对一个列表进行修剪(trim)，就是说，让列表只保留指定区间内的元素，不在指定区间之内的元素都将被删除）
lrem 根据参数 COUNT 的值，移除列表中与参数 VALUE 相等的元素。
COUNT 的值可以是以下几种：
count > 0 : 从表头开始向表尾搜索，移除与 VALUE 相等的元素，数量为 COUNT 。
count < 0 : 从表尾开始向表头搜索，移除与 VALUE 相等的元素，数量为 COUNT 的绝对值。
count = 0 : 移除表中所有与 VALUE 相等的值。

#lset（通过索引设置列表元素的值）
lset name 0 x

#llen（数组长度）
llen name

#blpop brpop brpoplpush（如果列表没有元素会阻塞列表直到等待超时或发现可弹出元素为止）

#linsert
LINSERT key BEFORE|AFTER pivot value
在列表的元素前或者后插入元素
```

### Set

```redis))
#sadd 
scard（获取集合的成员数）

sdiff(返回给定所有集合的差集）
sdiffstore（存储）
sinter（返回给定所有集合的交集）
sinterstore
sunion（返回所有给定集合的并集）
sunionstore

sismember（判断 member 元素是否是集合 key 的成员）
smembers（返回集合中的所有成员）
smove（将 member 元素从 source 集合移动到 destination 集合）
srem（移除集合中一个或多个成员）
spop（移除并返回集合中的一个随机元素）
srandmember （返回集合中一个或多个随机数）
```

### zset

```
同上，s改为z
```

### HyperLogLog

数据集 {1, 3, 5, 7, 5, 7, 8}， 那么这个数据集的基数集为 {1, 3, 5 ,7, 8}, 基数(不重复元素)为5。 基数估计就是在误差可接受的范围内，快速计算基数。

HyperLogLog 是用来做基数统计的算法，HyperLogLog 的优点是，在输入元素的数量或者体积非常非常大时，计算基数所需的空间总是固定 的、并且是很小的。每个 HyperLogLog 键只需要花费 12 KB 内存，就可以计算接近 2^64 个不同元素的基 数。

```
pfadd 添加指定元素到 HyperLogLog 中
pfcount 返回给定 HyperLogLog 的基数估算值
pfmerge 将多个 HyperLogLog 合并为一个 HyperLogLog
```

## 客户端

jedis lettuce redisson

### jedis

config/Jedisconfig.class

```
package com.gree.spring_boot_day01.config;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import redis.clients.jedis.JedisPool;
import redis.clients.jedis.JedisPoolConfig;

@Configuration
public class JedisConfig {
    @Value("${spring.redis.host}")
    private String host;
    @Value("${spring.redis.port}")
    private int port;
    @Value("${spring.redis.timeout}")
    private int timeout;
    @Value("${spring.redis.password}")
    private String password;
    @Value("${spring.redis.jedis.pool.max-active}")
    private int maxActive;
    @Value("${spring.redis.jedis.pool.min-idle}")
    private int minIdle;
    @Value("${spring.redis.jedis.pool.max-idle}")
    private int maxIdle;

    @Override
    public String toString() {
        return "JedisConfig{" +
                "host='" + host + '\'' +
                ", port=" + port +
                ", timeout=" + timeout +
                ", password='" + password + '\'' +
                ", maxActive=" + maxActive +
                ", minIdle=" + minIdle +
                ", maxIdle=" + maxIdle +
                '}';
    }

    @Bean
    public JedisPool redisPoolFactory() throws Exception {
        JedisPoolConfig jedisPoolConfig = new JedisPoolConfig();
        jedisPoolConfig.setMaxIdle(maxIdle);
        jedisPoolConfig.setMinIdle(minIdle);
        JedisPool jedisPool = new JedisPool(jedisPoolConfig, host, port, timeout, password);
        return jedisPool;
    }
}
```

application.yml

```
spring:
  redis:
    password: xiao9616
    port: 6379
    host: 172.28.4.109
    jedis:
      pool:
        max-active: 10
        min-idle: 2
        max-idle: 6
    timeout: 2000
```

test.java

```
@Autowired
private JedisConfig jedisConfig;

JedisPool jedisPool = jedisConfig.redisPoolFactory();
Jedis resource = jedisPool.getResource();
resource.set("xuan", "hao123");
```

## 集群

redis cluster

