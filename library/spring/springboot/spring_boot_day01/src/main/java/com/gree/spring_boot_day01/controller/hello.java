package com.gree.spring_boot_day01.controller;

import com.gree.spring_boot_day01.service.impl.UserServiceImpl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class hello {

    @Autowired
    private UserServiceImpl service;

    @RequestMapping("/hello")
    @ResponseBody
    public String hello() {
        return "I love 闫旭涛";
    }

    @RequestMapping("/test")
    @ResponseBody
    public String test() {
        return "覃工,专心上班";
    }

    @ResponseBody
    @RequestMapping("/redis")
    String redis() {
        String result = service.getString("xuan");
        return result;
    }
}
