package recursion;

/*递归；1.找重复 2.找变化（变化的量作为参数）3.找终止条件
* */
public class 递归 {

    public static void main(String[] args) {
        System.out.println(f1(10));
        f2(3,10);
        System.out.println(reverse("abcdefg", 6));
        System.out.println(fib(6));
        System.out.println(gbc(16,8));
    }

    /*  求阶乘
     * */
    static int f1(int n) {
        if (n == 1) {
            return 1;
        }
        return n * f1(n - 1);
    }

    /*打印i到j
     * */
    static void f2(int i, int j) {

        if (i > j) {
            return;
        }
        System.out.println(i);
        f2(i + 1, j);
    }

    /*反转字符串
     * */
    static String reverse(String src, int end) {
        if (end == 0) {
            return "" + src.charAt(0);
        }
        return src.charAt(end)+reverse(src,end-1);
    }

    /*斐波那契数组
     * */
    static int fib(int n) {
        if (n == 1 || n == 2) {
            return 1;
        }
        return fib(n - 1) + fib(n - 2);
    }

    /*最大公约数
     * */
    static int gbc(int a, int b) {
        if (b == 0) {
            return a;
        }
        return gbc(b, a % b);
    }
}
