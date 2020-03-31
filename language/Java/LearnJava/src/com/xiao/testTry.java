package com.xiao;

public class testTry {
    public static void main(String[] args){
        try {
            int[] i = new int[10];
            System.out.println(i[10]);

        } catch (Exception e) {
            System.out.println("异常");
            System.out.println(e.toString());
            System.out.println(e.getMessage());
            e.printStackTrace();
        }

        try {
            cal();
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            manule();
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            myexcep();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void cal() throws Exception{
        int i,j=10;
        j=10/0;
    }

    public static void manule() {
        throw new RuntimeException("手动抛出异常");
    }

    public static void myexcep(){
        throw new myexception("我的异常");
    }
}


