import java.util.HashMap;
import java.util.Map;

public class form {
    public static void main(String[] args) {
        Map<String, Integer> map = new HashMap<String, Integer>();
        map.put("id", 1);
        map.put("number", 121651);

        System.out.println(map.toString());
        String i="jijo";
        System.out.println(String.format("ji %s", i));
    }
}
