import java.util.List;

public class demo {
    public static void main(String[] args) {
        proxyImage proxyImage = new proxyImage("123.jpg");
        proxyImage.displayi();
        proxyImage.displayi();
        String s1 = "abc";
        String s2 = "abc";
        System.out.println(s1 == s2);
        System.err.println(s1.equals(s2));
    }

}
