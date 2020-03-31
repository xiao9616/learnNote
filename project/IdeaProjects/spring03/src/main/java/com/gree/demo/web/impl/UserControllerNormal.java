package com.gree.demo.web.impl;

import com.gree.demo.service.UserService;
import com.gree.demo.web.UserController;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Component;

@Component
public class UserControllerNormal implements UserController {
    @Autowired
    @Qualifier("normal")
    private UserService userService;
    public void add() {
        userService.add();
    }
}
