package logic;

import java.util.Random;
//找出数组中唯一一个成对的数 ，同理找出唯一一个落单的数
public class 唯一成对的数 {
    public static void main(String[] args) {
        int N = 11;
        int[] arr = new int[N];
        for (int i = 0; i < arr.length - 1; i++) {
            arr[i] = i + 1;
        }
        arr[arr.length - 1] = new Random().nextInt(N-1)+1;
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i]);
        }
        int x1=0;
        for (int i = 1; i <= N-1; i++) {
            x1 = x1 ^ (i);
        }
        for (int i = 0; i < N; i++) {
            x1=x1^arr[i];
        }
        System.out.println(x1);
    }

}
