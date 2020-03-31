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

```

### 高级命令

```

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

