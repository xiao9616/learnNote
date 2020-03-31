package compareable;

import javax.sound.midi.Soundbank;
import java.util.Comparator;
import java.util.Set;
import java.util.TreeSet;

public class test {
    public static void main(String[] args) {
        employee employee1 = new employee("xiao", 11, new myDate(6, 8, 1997));
        employee employee2 = new employee("wen", 11, new myDate(16, 8, 1997));
        employee employee3 = new employee("chu", 14, new myDate(6, 18, 1997));
        employee employee4 = new employee("chu", 12, new myDate(10, 17, 1997));
        employee employee5 = new employee("chu", 13, new myDate(5, 9, 1997));

        Set<employee> set = new TreeSet();
        set.add(employee1);
        set.add(employee2);
        set.add(employee3);
        set.add(employee4);
        set.add(employee5);

        for (Object e :
                set) {
            System.out.println(e);
        }

        //定制排序，使用comparator对象，用在类没有实现comparable接口的情况下
        Comparator com=new Comparator() {
            @Override
            public int compare(Object o1, Object o2) {
                if (o1 instanceof myDate && o2 instanceof myDate) {
                    myDate d1 = (myDate) o1;
                    myDate d2 = (myDate) o2;
                    if (d1.getYear() != d2.getYear()) {
                        return d1.getYear() - d2.getYear();
                    } else {
                        if (d1.getMonth() != d2.getMonth()) {
                            return d1.getMonth() - d2.getMonth();
                        } else {
                            return d1.getDay() - d2.getDay();
                        }
                    }

                }
                return 0;
            }
        };

        myDate d1 = new myDate(30, 12, 2019);
        myDate d2 = new myDate(30, 12, 2018);
        myDate d3 = new myDate(6, 9, 2018);
        myDate d4 = new myDate(5, 9, 2018);
        myDate d5 = new myDate(3, 8, 2017);

        Set<myDate> dateSet = new TreeSet<>(com);
        dateSet.add(d1);
        dateSet.add(d2);
        dateSet.add(d3);
        dateSet.add(d4);
        dateSet.add(d5);

        for (myDate d :
                dateSet) {
            System.out.println(d);
        }


    }
}
