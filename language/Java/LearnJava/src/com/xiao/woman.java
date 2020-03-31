package com.xiao;

public class woman extends Person {
    private boolean isBeauty;

    public woman() {
        super();
    }

    public woman(boolean isBeauty) {
        this.isBeauty = isBeauty;
    }

    public woman(String name, int id, boolean isBeauty) {
        super(name, id);
        this.isBeauty = isBeauty;
    }

    public boolean isBeauty() {
        return isBeauty;

    }

    public void setBeauty(boolean beauty) {
        isBeauty = beauty;
    }


    public void eat() {
        System.out.println("woman eat");
    }

    public void walk() {
        System.out.println("woman walk");
    }

}
