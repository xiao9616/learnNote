import java.util.ArrayList;

public class ContinuousSubarraySum {
    public static ArrayList<Integer> solution(int[] nums) {
        ArrayList<Integer> result = new ArrayList<Integer>();
        if (nums == null || nums.length <= 0) {
            return result;
        }
        int left = 0, right = 0, sum = 0;
        for (int i = 0; i < nums.length; i++) {
            sum += nums[i];
            if (sum < 0) {
                sum = 0;
                left=i+1;
            } else {
                right=i;
            }
        }
        result.add(left);
        result.add(right);
        return result;
    }

    public static void main(String[] args) {
        int[] nums = {-3, 1, 3, -3, 4,9};
        System.out.println(solution(nums));

    }
}

