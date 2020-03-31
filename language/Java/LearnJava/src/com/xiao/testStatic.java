package com.xiao;

import javax.sound.midi.Soundbank;

public class testStatic {
    private int i = 0;
    static int j=0;//表示类对象使用同一份
    public static void show() {//静态方法只能调用静态方法和属性，不能使用this super
                                //非静态方法可以调用静态方法和属性
        j=0;        //
        System.out.println("show");

    }
    public static void main(String[] args){
        testStatic.show();  //静态方法和属性可以直接通过类名.方法属性调用
    }
}
