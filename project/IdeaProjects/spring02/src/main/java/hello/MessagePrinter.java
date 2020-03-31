package hello;

import org.springframework.beans.factory.annotation.Autowired;

public class MessagePrinter {
    public MessagePrinter() {
        System.out.println("message printer");
    }

    public MessagePrinter(MessageService service) {
        this.service = service;
    }

    private MessageService service;

    @Autowired
    public void setService(MessageService service) {
        this.service = service;
    }

    public void printMessage() {
        String s = service.getMessage();
        System.out.println(s);
    }
}
