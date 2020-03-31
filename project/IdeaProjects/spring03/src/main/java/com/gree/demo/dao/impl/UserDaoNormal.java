package com.gree.demo.dao.impl;

import com.gree.demo.dao.UserDao;
import org.springframework.stereotype.Component;

@Component
public class UserDaoNormal implements UserDao {

    public void add() {
        System.out.println("添加用户到数据库");
    }
}
