package com.gree.spring_boot_day01;

import com.gree.spring_boot_day01.config.JedisConfig;
import com.gree.spring_boot_day01.config.JedisUtil;
import com.gree.spring_boot_day01.entity.Student;
import com.gree.spring_boot_day01.service.UserService;
import com.gree.spring_boot_day01.service.impl.UserServiceImpl;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPool;

@SpringBootTest
class SpringBootDay01ApplicationTests {
    @Autowired
    Student student;
    @Autowired
    private JedisConfig jedisConfig;
    @Autowired
    private UserServiceImpl service;
    @Autowired
    private JedisUtil jedisUtil;

    @Test
    public void close() {
        Jedis jedis = jedisUtil.getJedis();
        jedisUtil.close(jedis);
    }

    @Test
    void contextLoads() throws Exception {
        System.out.println(student);
        System.out.println(jedisConfig);
        JedisPool jedisPool = jedisConfig.redisPoolFactory();
        Jedis resource = jedisPool.getResource();
        resource.set("xuan", "hao123");

    }

    @Test
    void test() {
        String result = service.getString("xuan");
        System.out.println(result);
    }
}
