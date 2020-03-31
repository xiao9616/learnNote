import java.util.ArrayList;
import java.util.List;

public class LongestWords {
    public static ArrayList<String> solution(String[] dictionary) {
        ArrayList<String> result = new ArrayList<String>();
        if (dictionary == null || dictionary.length == 0) {
            return result;
        }
        for (String str : dictionary) {
            if (result.isEmpty() || str.length() > result.get(0).length()) {
                result.clear();
                result.add(str);
            } else if (str.length() == result.get(0).length()) {
                result.add(str);
            }
        }
        return result;
    }

    public static void main(String[] args) {
        String[] diction =
                {"dog",
                        "google",
                        "facebook",
                        "internationalization",
                        "blabla"};
        System.out.println(solution(diction));

    }
}



