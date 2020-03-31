package logic;

public class 所有数出现k次 {
    public static void main(String[] args) {
        int[] arr = {2, 2, 2, 7, 3, 3, 3, 5, 5, 5, 8, 8, 8};
        int len = arr.length;
        int k=3;
        char[][] kRadix = new char[len][];
        int maxLen = 0;
        for (int i = 0; i < len; i++) {
            kRadix[i] = new StringBuilder(Integer.toString(arr[i], k)).reverse().toString().toCharArray();
            if (kRadix[i].length >= maxLen) {
                maxLen = kRadix[i].length;
            }
        }
        int[] resArr = new int[maxLen];
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < maxLen; j++) {
                if (j <= kRadix[i].length) {
                    resArr[j] += 0;
                } else {
                    resArr[j] += (kRadix[i][j] - '0');
                }
            }
        }
        int res=0;
        for (int i = 0; i < maxLen; i++) {
            res += (resArr[i] % k) * (int) (Math.pow(k, i));
        }
        System.out.println(res);
    }
}
