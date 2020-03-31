 **1.集合框架**
 
    Collection接口
        |--------List接口
            |--------ArrayList
            |--------LinkedList
            |--------vector
        |--------Set接口
            |--------HashSet
            |--------TreeSet
            |--------LinkedHashSet
        
    Map接口
        |--------HashMap
        |--------TreeMap
        |--------LinkedHashMap
        |--------Hashtable
            |--------Properties
        
**2.遍历方式**  
    
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
    for (Object i:
            list) {
        System.out.println(i);
    }
    //3.for
    for (int i = 0; i < list.size(); i++) {
        System.out.println(list.get(i));
    }
    
**3.List**

    List list1 = new ArrayList();
    List list2 = new LinkedList();
    
**4.Set**

    Set set1 = new HashSet();
    Set set2 = new LinkedHashSet();//可以记录添加顺序
    Set set3 = new TreeSet();//1.需要添加相同类型2.实现接口Comparable的方法compareto
    
**5.Map**

    Map map1 = new HashMap();
    Map map2 = new LinkedHashMap();
    Map map3 = new TreeMap();
    
map的遍历

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
    
**6.Properties**

key,value都为string类型

