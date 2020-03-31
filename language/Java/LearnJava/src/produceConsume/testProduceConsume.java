package produceConsume;

class producer implements Runnable {
    Clerk clerk;

    public producer(Clerk clerk) {
        this.clerk = clerk;
    }

    @Override
    public void run() {
        System.out.println("开始生产");
        while (true) {
            clerk.addproduct();
        }
    }
}

class consumer implements Runnable {
    Clerk clerk;

    public consumer(Clerk clerk) {
        this.clerk = clerk;
    }

    @Override
    public void run() {
        while (true) {
            clerk.consumeproduct();
        }
    }
}

class Clerk {
    int products;

    public synchronized void addproduct() {
        if (products >= 20) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else {
            products++;
            System.out.println(Thread.currentThread().getName() + "生产了第" + products + "个产品");
            notifyAll();
        }
    }

    public synchronized void consumeproduct() {
        if (products < 0) {
            try {
                wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        } else {

            System.out.println(Thread.currentThread().getName() + "消费了第" + products + "个产品");
            products--;
            notifyAll();
        }
    }
}

public class testProduceConsume {
    public static void main(String[] args) {
        Clerk clerk = new Clerk();
        producer producer = new producer(clerk);
        consumer consumer = new consumer(clerk);
        Thread t1 = new Thread(producer);
        Thread t2 = new Thread(consumer);
        t1.setName("生产者");
        t2.setName("消费者");
        t1.start();
        t2.start();
    }
}
