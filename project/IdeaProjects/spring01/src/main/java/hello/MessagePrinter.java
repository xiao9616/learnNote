package hello;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

@Component
public class MessagePrinter {
    public MessagePrinter() {
        System.out.println("message printer");
    }

    private MessageService service;

    @Autowired(required = false)
    public void setService(MessageService service) {
        this.service = service;
    }

    public void printMessage() {
        String s = service.getMessage();
        System.out.println(s);
    }
}
