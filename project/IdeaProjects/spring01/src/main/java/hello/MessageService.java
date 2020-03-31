package hello;

import org.springframework.stereotype.Component;

//打印
@Component
public class MessageService {
    public MessageService() {
        System.out.println("message service");
    }

    public String getMessage() {
        return "hello world!";
    }
}
