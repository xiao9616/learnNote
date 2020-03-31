package com.xiao;

import java.io.*;

public class testIO {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        File file=new File("note/test.txt");
        System.out.println(file.getName());
        System.out.println(file.getPath());
        System.out.println(file.getAbsolutePath());
        System.out.println(file.getParent());
        System.out.println(file.getAbsoluteFile());
        System.out.println(file.exists());
        System.out.println(file.canWrite());
        System.out.println(file.isFile());
        System.out.println(file.isDirectory());
        System.out.println(file.lastModified());
        System.out.println(file.length());

        System.out.println("========================");
        //字节流stream 字符流reader writer 区别在于使用byte还是char
//        FileInputStream;
//        FileOutputStream;
//        FileReader;
//        FileWriter;

        FileInputStream fin = new FileInputStream(file);
        int b = fin.read();
        while (b != -1) {
            System.out.print((char)b);
            b = fin.read();
        }
        fin.close();

        FileOutputStream fout = new FileOutputStream(file);
        fout.write(new String("i love").getBytes());
        int c = 50;
        while (c < 100) {
            fout.write(c++);
        }
        fout.close();

        FileReader fileReader = new FileReader(file);
        FileWriter fileWriter = new FileWriter(new File("note/test1.txt"));
        char[] d = new char[24];
        int len;
        while ((len = fileReader.read(d)) != -1) {
            String s = new String(d, 0, len);
            System.out.println(s);
            fileWriter.write(d,0,len);
        }
        fileReader.close();
        fileWriter.close();

        System.out.println("===============");
        //处理流
//        BufferedInputStream；
//        BufferedOutputStream;
//        BufferedReader;
//        BufferedWriter;
        BufferedInputStream bin = new BufferedInputStream(new FileInputStream(new File("note/test.txt")));

        byte[] e = new byte[24];

        while ((len = bin.read(e)) != -1) {
            String string = new String(e, 0, len);
            System.out.println(string);

        }
        bin.close();

        System.out.println("==================");
        //转换流 字节流和字符流之间的转换
//        InputStreamReader;   字节->字符   解码
//        OutputStreamWriter;   字符->字节  编码
        FileInputStream fis = new FileInputStream(file);
        InputStreamReader isr = new InputStreamReader(fis, "GBK");
        BufferedReader br = new BufferedReader(isr);
        String str;
        while ((str = br.readLine()) != null) {
            System.out.println(str);
        }

        System.out.println("==================");
        //对象流 序列化 需要类实现序列化接口Serializable(包括属性)

        Person p1 = new Person("xiao", 12);
        ObjectOutputStream objectOutputStream = new ObjectOutputStream(new FileOutputStream("person.txt"));
        objectOutputStream.writeObject(p1);
        objectOutputStream.flush();
        objectOutputStream.close();

        //反序列化
        ObjectInputStream objectInputStream = new ObjectInputStream(new FileInputStream("person.txt"));
        Person p2 = (Person) objectInputStream.readObject();
        System.out.println(p2);

        System.out.println("==================");
        //随机访问流
//        RandomAccessFile
        RandomAccessFile randomAccessFile = new RandomAccessFile(new File("person.txt"), "rw");
        randomAccessFile.seek(10);
        System.out.println(randomAccessFile.readLine());

        System.out.println("==================");
        //打印流
//        PrintStream
//        PrintWriter
        FileOutputStream fos = new FileOutputStream(new File("note/print.txt"));
        PrintStream ps = new PrintStream(fos, true);
        System.setOut(ps);//下面的打印都会传到print.txt

        System.out.println("nihao");

        System.out.println("==================");
        //输入输出流
        InputStream is = System.in;
        InputStreamReader ir = new InputStreamReader(is);
        BufferedReader bufferedReader = new BufferedReader(ir);
        String s = bufferedReader.readLine();
        System.out.println(s.toUpperCase());
    }
}
