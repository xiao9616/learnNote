public class ReverseInteger {
    public static int solution(int n) {
        long result = 0;
        while (n != 0) {
            result = 10 * result + n % 10;
            n /= 10;
        }
        return (int) result;
    }

    public static void main(String[] args) {
        System.out.println(solution(-369));

    }
}
