package compareable;

import java.util.Objects;

public class employee implements Comparable{
    private String name;
    private Integer age;
    private myDate birthday;

    @Override
    public String toString() {
        return "employee{" +
                "name='" + name + '\'' +
                ", age=" + age +
                ", birthday=" + birthday +
                '}';
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public myDate getBirthday() {
        return birthday;
    }

    public void setBirthday(myDate birthday) {
        this.birthday = birthday;
    }

    public employee(String name, int age, myDate birthday) {
        this.name = name;
        this.age = age;
        this.birthday = birthday;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        employee employee = (employee) o;
        return age == employee.age &&
                Objects.equals(name, employee.name) &&
                Objects.equals(birthday, employee.birthday);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name, age, birthday);
    }

    //自然排序，实现comparable接口，按照name排序
    @Override
    public int compareTo(Object o) {
        if (o instanceof employee) {
            employee e = (employee) o;
            int i = this.name.compareTo(e.name);
            if (i == 0) {
                return this.age.compareTo(e.age);
            } else {
                return i;
            }
        }
        return 0;
    }

}
