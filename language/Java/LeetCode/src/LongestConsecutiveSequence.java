import java.util.HashSet;
import java.util.Set;

public class LongestConsecutiveSequence {
    public static int solution(int[] nums) {
        if (nums == null || nums.length <= 0) {
            return 0;
        }
        HashSet<Object> sets = new HashSet<>(nums.length);
        for (int num : nums) {
            sets.add(num);
        }

        int result = 1;
        for (int num : nums) {
            int seq = 1;
            int right = num;
            int left = num;
            while (sets.contains(++right)) {
                ++seq;
                sets.remove(right);
            }
            while (sets.contains(--left)) {
                ++seq;
                sets.remove(left);
            }
            sets.remove(num);
            if (seq > result) {
                result = seq;
            }

        }
        return result;

    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 3, 7, 8, 5, 6};
        System.out.println(solution(nums));
    }
}
