# LeetCode

## Longest Consecutive Sequence

```java
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
```

## ReverseInteger

```java
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
```

## GrayCode

```
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
```

## findMissing

```java
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

```

## LongestWords

```java
import java.util.ArrayList;

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
```

