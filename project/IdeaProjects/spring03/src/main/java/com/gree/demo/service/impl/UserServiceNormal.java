package com.gree.demo.service.impl;

import com.gree.demo.dao.UserDao;
import com.gree.demo.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component("normal")
public class UserServiceNormal implements UserService {

    private UserDao userDao;

    public UserServiceNormal() {
    }

    public UserServiceNormal(UserDao userDao) {
        this.userDao = userDao;
    }

    public void add() {
        userDao.add();
    }
}
