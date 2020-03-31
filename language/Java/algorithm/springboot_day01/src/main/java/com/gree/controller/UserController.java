package com.gree.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.Map;

@Controller
public class UserController {
    @RequestMapping("/login")
    public String register(Map<String,Object> map){
        map.put("name", "肖文轩");
        System.out.println("注册过程");
        return "login";
    }
}
