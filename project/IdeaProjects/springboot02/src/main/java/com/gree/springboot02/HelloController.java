package com.gree.springboot02;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HelloController {
    @Autowired
    JdbcTemplate jdbcTemplate;
    @RequestMapping(value = "/search", method = RequestMethod.GET)
    public String search(){
        String sql = "SELECT mobile FROM user WHERE id = ?";
        String mobile = (String) jdbcTemplate.queryForObject(sql, new Object[]{1}, String.class);
        return "hello" + mobile;
    }
}
