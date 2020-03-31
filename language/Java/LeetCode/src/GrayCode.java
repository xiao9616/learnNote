import java.util.ArrayList;

public class GrayCode {
    public static ArrayList<Integer> solution(int n) {
        ArrayList<Integer> result = new ArrayList<>();
        for (int i = 0; i < (1 << n); i++) {
            result.add(i >> 1 ^ i);
        }
        return result;
    }

    public static void main(String[] args) {
        ArrayList<Integer> result = new ArrayList<>();
        result = solution(3);
        for (int i = 0; i < result.size(); i++) {
            System.out.println(Integer.toBinaryString(result.get(i)));
        }
    }
}
