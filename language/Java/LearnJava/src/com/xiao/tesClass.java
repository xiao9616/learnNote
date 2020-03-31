package com.xiao;

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

public class tesClass {
    public static void main(String[] args) throws NoSuchFieldException, IllegalAccessException, InstantiationException, NoSuchMethodException, InvocationTargetException {
        Class cla = Person.class;

        //1.创建运行时的person的对象
        Person p1 = (Person) cla.newInstance();
        System.out.println(p1);

        //2.通过反射调用运行时类的属性
        Field name = cla.getField("name");
        name.set(p1,"xiao");
        System.out.println(p1);

        //3.通过反射调用运行时类的方法
        Method m1 = cla.getMethod("eat");
        m1.invoke(p1);
    }
}
