package hello;


import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class ApplicationSpring {
    public static void main(String[] args) {
        System.out.println("applicationSpring");
        //初始化spring容器
        //从容器中获取对象
        ApplicationContext context = new ClassPathXmlApplicationContext("applicationContext.xml");
        MessagePrinter printer = (MessagePrinter) context.getBean("printer");
        printer.printMessage();
    }
}
