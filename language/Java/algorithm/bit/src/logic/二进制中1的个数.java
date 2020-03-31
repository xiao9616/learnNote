package logic;
//求二进制中1的个数 同理判断一个数是不是2的整数次方（二进制只有一个1）
public class 二进制中1的个数 {
    public static void main(String[] args) {
        int count = 0;
        int N=7;
        while (N != 0) {
            N=N&(N-1); //抹掉N的最低位的1
            count++;
        }
        System.out.println(count);
    }
}
