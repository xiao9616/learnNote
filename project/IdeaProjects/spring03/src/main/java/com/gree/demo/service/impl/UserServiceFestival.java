package com.gree.demo.service.impl;

import com.gree.demo.dao.UserDao;
import com.gree.demo.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;

@Component("festival")
public class UserServiceFestival implements UserService {
    @Autowired
    private UserDao userDao;

    public void add() {
        userDao.add();
    }
}
