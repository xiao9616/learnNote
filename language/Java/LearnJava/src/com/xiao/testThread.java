package com.xiao;

class subThread extends Thread {
    @Override
    public void run() {
        Thread.currentThread().setName("子线程");
        for (int i = 0; i < 1000; i++) {
            try {
                Thread.currentThread().sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(i + ":" + Thread.currentThread().getName());
        }
    }
}

class impThread implements Runnable {
    @Override
    public void run() {
        for (int i = 0; i < 1000; i++) {
            System.out.println(i + ":" + Thread.currentThread().getName());
        }
    }
}

class window implements Runnable {
    int tickets = 100;//共享数据
    Object obj = new Object();

    @Override
    public void run() {
        while (true) {
            synchronized (obj) {
                if (tickets > 0) {
                    try {
                        Thread.currentThread().sleep(10);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    System.out.println(Thread.currentThread().getName() + "票号" + tickets--);

                } else {
                    break;
                }
            }

        }
    }
}

public class testThread {
    public static void main(String[] args) {
        //多线程的两种方式；
        //1.继承Thread类
        //2.实现Runable接口
        subThread st = new subThread();
        impThread impt = new impThread();
        Thread t1 = new Thread(impt);
        st.start();
        t1.start();
        st.setPriority(Thread.MAX_PRIORITY);
        Thread.currentThread().setName("主线程");
        for (int i = 0; i < 1000; i++) {
            System.out.println(i);
//            if (i % 10 == 0) {
//                Thread.currentThread().yield();//释放当前cpu的执行权
//            }
            if (i == 20) {
                try {
                    st.join();//加载线程，直到该线程运行完毕
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
        System.out.println(st.isAlive());

        System.out.println("========================");
        window win1 = new window();
        Thread thread11 = new Thread(win1);
        Thread thread22 = new Thread(win1);
        Thread thread33 = new Thread(win1);
        thread11.start();
        thread22.start();
        thread33.start();
        //线程同步
        //1.同步代码块
        //synchronized (Object obj) obj 为对象锁，在实现的方式中，可以用this替代
        //2.同步方法
//        方法前面+synchronized,内部使用的是this
    }

}
