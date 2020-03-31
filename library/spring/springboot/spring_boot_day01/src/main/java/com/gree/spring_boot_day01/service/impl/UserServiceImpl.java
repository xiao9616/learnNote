package com.gree.spring_boot_day01.service.impl;

import com.gree.spring_boot_day01.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import redis.clients.jedis.Jedis;
import redis.clients.jedis.JedisPool;

@Service
public class UserServiceImpl implements UserService {
    @Autowired
    private JedisPool jedisPool;
    String val = null;

    @Override
    public String getString(String key) {
        Jedis jedis = jedisPool.getResource();
        if (jedis.exists(key)) {
            val = jedis.get(key);
        } else {
            System.out.println("null");
            jedis.set(key, "xiao");
        }
        jedis.close();
        return val;

    }
}
