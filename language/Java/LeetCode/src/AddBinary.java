public class AddBinary {
    public static String solution(String a, String b) {
        if (a==null||a.length()==0) return b;
        if (b==null||b.length()==0) return a;

        StringBuilder sb = new StringBuilder();
        int alen = a.length();
        int blen = b.length();
        int carry = 0;
        for (int ai = alen - 1, bi = blen - 1; ai >= 0 || bi >= 0; ai--, bi--) {
            int anum = (ai < 0) ? 0 : a.charAt(ai) - '0';
            int bnum = (bi < 0) ? 0 : b.charAt(bi) - '0';
            int num=(anum+bnum+carry)%2;
            carry=(anum+bnum+carry)/2;
            sb.append(num);
        }
        if (carry == 1) {
            sb.append(1);
        }
        sb.reverse();
        String result = sb.toString();
        return result;
    }

    public static void main(String[] args) {
        System.out.println(solution("011","1000"));
    }
}

