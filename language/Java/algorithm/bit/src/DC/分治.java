package DC;

/*分治三步骤：
分解：将原问题划分为一系列子问题
解决：递归的解决各个子问题
合并：将子问题的结果合并成原问题的解
* */

public class 分治 {
    public static void main(String[] args) {

    }

    public static void quicksort(int[] A,int p,int r){
        if (p < r) {
            int q = partition(A, p, r);  //寻找主元，
            quicksort(A, p, q - 1);
            quicksort(A, q + 1, r);
        }
    }

    public static int partition(int[] A,int p,int r) { //单向扫描法
        int pivot = A[p];
        int sp = p + 1;
        int bigger = r;
        while (sp <= bigger) {
            if (A[sp] <= A[pivot]) {
                sp++;
            } else {
                swap(A,sp,bigger);
                bigger--;
            }
        }
        swap(A, p, bigger);
        return bigger;
    }

    //双向扫描法
    public static int partition1(int[] A, int p, int r) {
        int pivot = A[p];
        int left=p+1;
        int right = r;
        while (left <= right) {
            while(left<=right && A[left]<=pivot) left++;
            while(left<=right && A[right]>pivot) right++;
            if (left < right) {
                wap(A, left, right);
            }
        }
        swap(A, p, right);
        return right;
    }


}


