package com.gree.demo.service;

import com.gree.demo.Appconfig;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = Appconfig.class)
public class UserServiceTest {
    @Autowired
    @Qualifier("festival")
    private UserService userService;

    @Test
    public void testAdd() {
        userService.add();
    }
}
