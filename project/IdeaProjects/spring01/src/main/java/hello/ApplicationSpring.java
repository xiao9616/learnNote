package hello;

import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.annotation.ComponentScan;

@ComponentScan
public class ApplicationSpring {
    public static void main(String[] args) {
        System.out.println("applicationSpring");
        //初始化spring容器
        ApplicationContext contex = new AnnotationConfigApplicationContext(AppConfig.class);
        //从容器中获取对象
        MessagePrinter printer = contex.getBean(MessagePrinter.class);

        printer.printMessage();
    }
}
