package com.xiao;

import java.util.Objects;

public class man extends Person {
    private boolean isStrong;

    public man() {
        super();
    }

    public man(boolean isStrong) {
        this.isStrong = isStrong;
    }

    public man(String name, int id, boolean isStrong) {
        super(name, id);
        this.isStrong = isStrong;
    }

    public boolean isStrong() {
        return isStrong;
    }

    public void setStrong(boolean strong) {
        isStrong = strong;
    }


    public void eat() {
        System.out.println(super.getName());
        System.out.println("man eat");

    }


    public void walk() {
        System.out.println("man walk");
    }

}
