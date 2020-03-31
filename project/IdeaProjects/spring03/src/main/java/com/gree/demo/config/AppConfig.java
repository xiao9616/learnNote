package com.gree.demo.config;

import com.gree.demo.dao.UserDao;
import com.gree.demo.dao.impl.UserDaoNormal;
import com.gree.demo.service.UserService;
import com.gree.demo.service.impl.UserServiceNormal;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class AppConfig {
    @Bean
    public UserDao userDaoNormal() {
        return new UserDaoNormal();
    }

    @Bean
    public UserServiceNormal userServiceNormal(UserDao userDao) {
        return new UserServiceNormal(userDao);
    }
}

