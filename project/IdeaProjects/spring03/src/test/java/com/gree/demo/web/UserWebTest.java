package com.gree.demo.web;

import com.gree.demo.Appconfig;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes = Appconfig.class)
public class UserWebTest {
    @Autowired
    private UserController userController;

    @Test
    public void testAdd() {
        userController.add();
    }
}
