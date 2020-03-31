package com.xiao;

class printNum implements Runnable {
    int num = 1;

    @Override
    public void run() {
        while (true) {
            synchronized (this) {
                notify();
                if (num < 100) {
                    try {
                        Thread.currentThread().sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() + ":" + num++);
                } else {
                    break;
                }
                try {
                    wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}

public class threadCommunication {
    public static void main(String[] args){
        printNum pn = new printNum();
        Thread t1 = new Thread(pn);
        Thread t2 = new Thread(pn);

        t1.setName("A");
        t2.setName("B");

        t1.start();
        t2.start();
    }
}
