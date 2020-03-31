public class findMissing {
    public static int solution(int[] nums, int N) {
        int x1 = 0;
        for (int i = 0; i <= N; i++) {
            x1 ^= i;
        }
        int x2 = 0;
        for (int i = 0; i < nums.length; i++) {
            x2 ^= nums[i];
        }
        return x1 ^ x2;
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 5, 6,0,7};
        System.out.println(solution(nums,7));
    }
}
