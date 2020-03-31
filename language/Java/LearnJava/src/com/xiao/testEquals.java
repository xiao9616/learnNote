package com.xiao;

public class testEquals {
    public static void main(String[] args) {
        int i = 12;
        float j = 12.0f;
        System.out.println(i == j);
        System.out.println("=============================================");

        Object object1 = new Object();
        Object object2 = new Object();
        System.out.println(object1 == object2);//false ==比较地址值
        System.out.println(object1.equals(object2));//false  object.equals比较是地址值
        System.out.println("=============================================");

        String s1 = new String("aa");
        String s2 = new String("aa");
        System.out.println(s1 == s2);//false
        System.out.println(s1.equals(s2));//true  string等包装类重写了equals方法
        System.out.println("=============================================");

        Person p1 = new man("xiao", 26, true);
        Person p2 = new woman("chuchu", 8, true);
        Person p3 = new woman("chuchu", 8, true);
        System.out.println(p2.equals(p3));
        System.out.println(p1);
        System.out.println(object1);
    }
}
