### 摘要

假设你正在爬楼梯，需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶，你有多少种不同的方法可以爬到楼顶呢？

### 解决方案
#### 方法一：暴力法

**算法**

在暴力法中，我们将会把所有可能爬的阶数进行组合，也就是 1 和 2 。而在每一步中我们都会继续调用 *climbStairs* 这个函数模拟爬 *1* 阶和 *2* 阶的情形，并返回两个函数的返回值之和。

*
climbStairs(i,n)=(i + 1, n) + climbStairs(i + 2, n)
*

其中 *i* 定义了当前阶数，而 *n* 定义了目标阶数。

```java [EGKie4cS-Java]
public class Solution {
    public int climbStairs(int n) {
        climb_Stairs(0, n);
    }
    public int climb_Stairs(int i, int n) {
        if (i > n) {
            return 0;
        }
        if (i == n) {
            return 1;
        }
        return climb_Stairs(i + 1, n) + climb_Stairs(i + 2, n);
    }
}
```


**复杂度分析**

* 时间复杂度：*O(2^n)*，树形递归的大小为 *2^n* 。

    在 n = 5 时的递归树将是这样的：

     [Climbing_Stairs](https://pic.leetcode-cn.com/07a21d45a33309d39925127eb0a8611fce5212cb932e4a6fe9914b30c885d1f6-file_1555697913334)

* 空间复杂度：*O(n)*，递归树的深度可以达到 *n* 。




---

#### 方法二：记忆化递归

**算法**

在上一种方法中，我们计算每一步的结果时出现了冗余。另一种思路是，我们可以把每一步的结果存储在 *memo* 数组之中，每当函数再次被调用，我们就直接从 *memo* 数组返回结果。

在 *memo* 数组的帮助下，我们得到了一个修复的递归树，其大小减少到 *n*。

```java [8ddWTSpm-Java]
public class Solution {
    public int climbStairs(int n) {
        int memo[] = new int[n + 1];
        return climb_Stairs(0, n, memo);
    }
    public int climb_Stairs(int i, int n, int memo[]) {
        if (i > n) {
            return 0;
        }
        if (i == n) {
            return 1;
        }
        if (memo[i] > 0) {
            return memo[i];
        }
        memo[i] = climb_Stairs(i + 1, n, memo) + climb_Stairs(i + 2, n, memo);
        return memo[i];
    }
}
```


**复杂度分析**

* 时间复杂度：*O(n)*，树形递归的大小可以达到 *n*。
* 空间复杂度：*O(n)*，递归树的深度可以达到 *n*。




---

#### 方法三：动态规划

**算法**

不难发现，这个问题可以被分解为一些包含最优子结构的子问题，即它的最优解可以从其子问题的最优解来有效地构建，我们可以使用动态规划来解决这一问题。

第 *i* 阶可以由以下两种方法得到：

1. 在第 *(i-1)* 阶后向上爬一阶。

2. 在第 *(i-2)* 阶后向上爬 *2* 阶。
   
所以到达第 *i* 阶的方法总数就是到第 *(i-1)* 阶和第 *(i-2)* 阶的方法数之和。

令 *dp[i]* 表示能到达第 *i* 阶的方法总数：

*
dp[i]=dp[i-1]+dp[i-2]
*

示例：



  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide1.JPG)  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide2.JPG)  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide3.JPG)  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide4.JPG)  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide5.JPG)  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide6.JPG)  [1000](https://pic.leetcode-cn.com/Figures/70_Climbing_StairsSlide7.JPG) 



```java [oXFdbBkn-Java]
public class Solution {
    public int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        int[] dp = new int[n + 1];
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
}
```


**复杂度分析**

* 时间复杂度：*O(n)*，单循环到 *n* 。

* 空间复杂度：*O(n)*，*dp* 数组用了 *n* 的空间。




---

#### 方法四：斐波那契数

**算法**

在上述方法中，我们使用 *dp* 数组，其中 *dp[i]=dp[i-1]+dp[i-2]*。可以很容易通过分析得出 *dp[i]* 其实就是第 *i* 个斐波那契数。

*
Fib(n)=Fib(n-1)+Fib(n-2)
*

现在我们必须找出以 *1* 和 *2* 作为第一项和第二项的斐波那契数列中的第 *n* 个数，也就是说 *Fib(1)=1* 且 *Fib(2)=2*。

```java [KX2MK9x4-Java]
public class Solution {
    public int climbStairs(int n) {
        if (n == 1) {
            return 1;
        }
        int first = 1;
        int second = 2;
        for (int i = 3; i <= n; i++) {
            int third = first + second;
            first = second;
            second = third;
        }
        return second;
    }
}
```


**复杂度分析**

* 时间复杂度：*O(n)*，单循环到 *n*，需要计算第 *n* 个斐波那契数。

* 空间复杂度：*O(1)*，使用常量级空间。




---

#### 方法五：Binets 方法

**算法**

这里有一种有趣的解法，它使用矩阵乘法来得到第 *n* 个斐波那契数。矩阵形式如下：

![\left\[{\begin{array}{cc}F_{n+1}&F_n\\F_n&F_{n-1}\end{array}}\right\]=\left\[{\begin{array}{cc}1&1\\1&0\end{array}}\right\]^{n} ](./p___left__{begin{array}{cc}_F_{n+1}_&_F_n___F_n_&_F_{n-1}_____end{array}_}_right__=_left__{begin{array}{cc}_1_&_1___1_&_0_____end{array}_}_right_^{n}__.png) 

令 ![Q=\left\[{\begin{array}{cc}F_{n+1}&F_n\\F_n&F_{n-1}\end{array}}\right\] ](./p__Q=left__{begin{array}{cc}_F_{n+1}_&_F_n___F_n_&_F_{n-1}_____end{array}_}_right__.png) 。按照此方法，第 *n* 个斐波那契数可以由 *{Q^{n-1}}_{[0,0]}* 给出。

让我们试着证明一下。

我们可以使用数学归纳法来证明这一方法。易知，该矩阵给出了第 *3* 项（基本情况）的正确结果。由于 ![Q^2=\left\[{\begin{array}{cc}2&1\\1&1\end{array}}\right\] ](./p__Q^2_=_left__{begin{array}{cc}_2_&_1___1_&_1_____end{array}_}_right__.png) 。这证明基本情况是成立的。

假设此方法适用于查找第 *n* 个斐波那契数，即 *F_n={Q^{n-1}}_{[0,0]}*，那么：
![Q^{n-1}=\left\[{\begin{array}{cc}F_{n}&F_{n-1}\\F_{n-1}&F_{n-2}\end{array}}\right\] ](./p___Q^{n-1}=left__{begin{array}{cc}_F_{n}_&_F_{n-1}___F_{n-1}_&_F_{n-2}_____end{array}_}_right___.png) 

现在，我们需要证明在上述两个条件为真的情况下，该方法可以有效找出第 *(n+1)* 个斐波那契数，即，*F_{n+1}={Q^{n}}_{[0,0]}*。

证明：![Q^{n}=\left\[{\begin{array}{cc}F_{n}&F_{n-1}\\F_{n-1}&F_{n-2}\end{array}}\right\]\left\[{\begin{array}{cc}1&1\\1&0\end{array}}\right\] ](./p__Q^{n}_=_left__{begin{array}{cc}_F_{n}_&_F_{n-1}___F_{n-1}_&_F_{n-2}_____end{array}_}_right_left__{begin{array}{cc}_1_&_1___1_&_0_____end{array}_}_right__.png) .
 ![Q^{n}=\left\[{\begin{array}{cc}F_{n}+F_{n-1}&F_n\\F_{n-1}+F_{n-2}&F_{n-1}\end{array}}\right\] ](./p__Q^{n}_=_left__{begin{array}{cc}_F_{n}+F_{n-1}_&_F_n___F_{n-1}+F_{n-2}_&_F_{n-1}____end{array}_}_right__.png) 
 ![Q^{n}=\left\[{\begin{array}{cc}F_{n+1}&F_n\\F_n&F_{n-1}\end{array}}\right\] ](./p__Q^{n}_=_left__{begin{array}{cc}_F_{n+1}_&_F_n___F_n_&_F_{n-1}_____end{array}_}_right__.png) 

从而， *F_{n+1}={Q^{n}}_{[0,0]}*，得证。

我们需要为我们的问题做的唯一改动就是将斐波那契数列的初始项修改为 2 和 1 来代替原来的 1 和 0 。或者，另一种方法是使用相同的初始矩阵 *Q* 并使用 *result = {Q^{n}}_{[0,0]}* 得出最后结果。发生这种情况的原因是我们必须使用原斐波那契数列的第 2 项和第 3 项作为初始项。


 ```java [q7BugGJk-Java]
 public class Solution {
    public int climbStairs(int n) {
        int[][] q = {{1, 1}, {1, 0}};
        int[][] res = pow(q, n);
        return res[0][0];
    }
    public int[][] pow(int[][] a, int n) {
        int[][] ret = {{1, 0}, {0, 1}};
        while (n > 0) {
            if ((n & 1) == 1) {
                ret = multiply(ret, a);
            }
            n >>= 1;
            a = multiply(a, a);
        }
        return ret;
    }
    public int[][] multiply(int[][] a, int[][] b) {
        int[][] c = new int[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
            }
        }
        return c;
    }
}
```


**复杂度分析**

* 时间复杂度：*O(log(n))*，遍历 *log(n)* 位。

* 空间复杂度：*O(1)*，使用常量级空间。

对时间复杂度的证明：

假设我们需要计算矩阵 *M* 的 *n* 次幂。假设，*n* 是 2 的幂。因此，*n = 2^i*，![i\in\mathbb{N} ](./p__iinmathbb{N}_.png) ，其中 ![\mathbb{N} ](./p__mathbb{N}_.png)  表示自然数的集合（包括 0）。我们可以用树形结构进行表示：

 [Climbing Stairs](https://pic.leetcode-cn.com/f2caba82e1703ff580df436aad9c45c47d7ba8aac2f66c1f196e4eeef5b29fbd-file_1555697820512)


这意味着：![M^n=M^{n/2}.M^{n/2}=....=\prod_{1}^{n}M^{1} ](./p__M^n_=_M^{n_2}.M^{n_2}_=_...._=_prod_{1}^{n}_M^{1}_.png) 

所以，要计算  *M^{n}*，我们先要计算 *M^{n/2}* 并将其与自身相乘。而为了计算 *M^{n/2}*，我们需要对 *M^{n/4}* 进行类似的操作，并依此类推。

显然，树的高度为 *log_{2}n*。

让我们来估计一下 *M^{n}* 计算所需要的时间。矩阵 *M* 在幂运算过程中大小保持不变。因此，进行两矩阵幂乘的空间复杂度是 *O(1)*。我们需要执行 *log_2{n}* 次这样的乘法。所以，计算 *M^{n}* 的时间复杂度为 *O(log_{2}n)*。

如果数字 *n* 不是2的幂，我们可以使用其二进制表示将其转化为 2 的幂次项之和：

![n=\sum_{p\inP}2^{p},\text{where}P\subset\mathbb{N} ](./p___n=_sum_{pin_P}_2^{p},_text{where_}Psubsetmathbb{N}__.png) 

因此，我们可以使用以下方法获得最终结果：

![M^{n}=\prod_{p\inP}M^{2^{p}} ](./p___M^{n}_=_prod_{pin_P}_M^{2^{p}}__.png) 

这是我们在实现中使用的方法。 同样，时间复杂度仍为 *O(log_{2}n)*，因为乘法次数的限制为 *O(log_{2}n)*。





---

#### 方法六：斐波那契公式

**算法**

我们可以使用这一公式来找出第 *n* 个斐波那契数：

![F_n=1/\sqrt{5}\left\[\left(\frac{1+\sqrt{5}}{2}\right)^{n}-\left(\frac{1-\sqrt{5}}{2}\right)^{n}\right\] ](./p___F_n_=_1_sqrt{5}left__left_frac{1+sqrt{5}}{2}right_^{n}_-_left_frac{1-sqrt{5}}{2}right_^{n}_right___.png) 

对于给定的问题，斐波那契序列将会被定义为 *F_0 = 1*，*F_1= 1*，*F_1= 2*，*F_{n+2}= F_{n+1} + F_n*。尝试解决这一递归公式的标准方法是设出  *F_n*，其形式为 *F_n= a^n*。然后，自然有 *F_{n+1} = a^{n+1}* 和 *F_{n+2}= a^{n+2}*，所以方程可以写作 *a^{n+2}= a^{n+1}+ a^n*。如果我们对整个方程进行约分，可以得到 *a^2= a + 1* 或者写成二次方程形式 *a^2 - a- 1= 0*。

对二次公式求解，我们得到：

![a=1/\sqrt{5}\left(\left(\frac{1\pm\sqrt{5}}{2}\right)\right) ](./p___a=1_sqrt{5}left_left_frac{1pm_sqrt{5}}{2}right_right___.png) 

一般解采用以下形式：

![F_n=A\left(\frac{1+\sqrt{5}}{2}\right)^{n}+B\left(\frac{1-\sqrt{5}}{2}\right)^{n} ](./p___F_n_=_Aleft_frac{1+sqrt{5}}{2}right_^{n}_+_Bleft_frac{1-sqrt{5}}{2}right_^{n}__.png) 

*n=0* 时，有 *A + B = 1*

*n=1* 时，有 ![A\left(\frac{1+\sqrt{5}}{2}\right)+B\left(\frac{1-\sqrt{5}}{2}\right)=1 ](./p__Aleft_frac{1+sqrt{5}}{2}right__+_Bleft_frac{1-sqrt{5}}{2}right__=_1_.png) 

解上述等式，我们得到：

![A=\left(\frac{1+\sqrt{5}}{2\sqrt{5}}\right),B=\left(\frac{1-\sqrt{5}}{2\sqrt{5}}\right) ](./p___A_=_left_frac{1+sqrt{5}}{2sqrt{5}}right_,_B_=_left_frac{1-sqrt{5}}{2sqrt{5}}right___.png) 

将 *A* 和 *B* 的这些值带入上述的一般解方程中，可以得到：

![F_n=1/\sqrt{5}\left(\left(\frac{1+\sqrt{5}}{2}\right)^{n+1}-\left(\frac{1-\sqrt{5}}{2}\right)^{n+1}\right) ](./p___F_n_=_1_sqrt{5}left__left_frac{1+sqrt{5}}{2}right_^{n+1}_-_left_frac{1-sqrt{5}}{2}right_^{n+1}_right___.png) 

```java [ufJvFTqa-Java]
public class Solution {
    public int climbStairs(int n) {
        double sqrt5=Math.sqrt(5);
        double fibn=Math.pow((1+sqrt5)/2,n+1)-Math.pow((1-sqrt5)/2,n+1);
        return (int)(fibn/sqrt5);
    }
}
```


**复杂度分析**

* 时间复杂度：*O(log(n))*，*pow* 方法将会用去 *log(n)* 的时间。

* 空间复杂度：*O(1)*，使用常量级空间。