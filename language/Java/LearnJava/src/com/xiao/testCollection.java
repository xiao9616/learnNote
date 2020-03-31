package com.xiao;


import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.util.*;

public class testCollection {
    public static void main(String[] args) throws IOException {
        ArrayList<Object> list = new ArrayList<>();
        list.add(1);
        list.add(2);
        list.add(3);
        //三种遍历方式
        //1.迭代器
        Iterator it = list.iterator();
        while (it.hasNext()) {
            System.out.println(it.next());
        }
        //2.foreach
        for (Object i :
                list) {
            System.out.println(i);
        }
        //3.for
        for (int i = 0; i < list.size(); i++) {
            System.out.println(list.get(i));
        }

        System.out.println(list.toString());

        List list1 = new ArrayList();
        List list2 = new LinkedList();

        Set set1 = new HashSet();
        Set set2 = new LinkedHashSet();//可以记录添加顺序
        Set set3 = new TreeSet();

        Map map1 = new HashMap();
        Map map2 = new LinkedHashMap();
        Map map3 = new TreeMap();

        map1.put("a", 1);
        map1.put("b", 2);
        map1.put("c", 3);

        //1.遍历keyset
        Set keyset = map1.keySet();
        for (Object i :
                keyset) {
            System.out.println(i);
        }
        //2.遍历valueset
        Collection values = map1.values();
        for (Object i :
                values) {
            System.out.println(i);
        }
        //3.遍历entryset
        Set entryset = map1.entrySet();
        for (Object i :
                entryset) {
            Map.Entry entry = (Map.Entry) i;
            System.out.println(entry.getKey() + ":" + entry.getValue());
        }

        Properties pro = new Properties();
        pro.load(new FileInputStream(new File("com/xiao/jdbc.properties")));
        String name = pro.getProperty("user");
        System.out.println(name);
    }
}
