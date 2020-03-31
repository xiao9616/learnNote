package com.gree.demo;

import org.junit.Test;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class NotepadTest {
    @Test
    public void test01() {
        ClassPathXmlApplicationContext context = new ClassPathXmlApplicationContext("applicationConfig.xml");
        Notepad note = (Notepad) context.getBean("notepad");
        Notepad note2 = (Notepad) context.getBean("notepad");
    }
}
