package com.xiao;

public class testInteger {
    public static void main(String[] args){
        Integer int1 = new Integer(1);
        Float f = new Float(12.0f);
        System.out.println(int1);
        System.out.println(f);
        int i=int1.intValue();
        System.out.println(i);

        int j=int1;//自动拆箱
        Integer int2=i;//自动装箱

        String str = String.valueOf(j);//转字符串
        Integer k=Integer.parseInt(str);//从字符串转

    }
}
