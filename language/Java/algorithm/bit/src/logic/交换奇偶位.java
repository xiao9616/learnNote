package logic;

public class 交换奇偶位 {
    int a = 9;

    public static void main(String[] args) {
        System.out.println(m(9));
    }
    private static int m(int i) {
        int ou=i&0xaaaaaaaa;
        int ji=i&0x55555555;
        return (ou >> 1) ^ (ji << 1);
    }
}


