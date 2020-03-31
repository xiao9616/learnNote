package hello;

//打印

import java.util.List;

public class MessageService {
    public MessageService(String name) {
        this.name = name;
    }

    private String name;
    private List<String> list;

    public MessageService(String name, List<String> list) {
        this.name = name;
        this.list = list;
    }

    public MessageService() {
        System.out.println("message service");
    }

    public String getMessage() {
        return "hello world!";
    }
}
