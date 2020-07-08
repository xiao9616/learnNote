### 解题思路
执行用时 :28 ms, 在所有 Python3 提交中击败了99.93%的用户
设一个左指针在0下标处，右指针在末下标处
设历史上达到的最大高度h初始值为0，初始接水面积ds = 0

a.分别拿到左右指针所对应的列高，每次找到比较矮的一个，得到其高度new_h = min(left, right)
b.判断new_h是否大于h，如果大于，则让ds新增可以接水的面积(包括柱子的面积)为 历史高度差(h - new_h) * 最大宽度(right - left + 1) [因为之前h以下的高度已经被累加过了]，然后刷新h的记录；反之，不作操作
c.而后将这个指针靠另一侧移动(如果左指针矮，则下标+1，右指针矮则下标-1)，并从a.步开始重复，直到左右两指针的坐标相等时结束

我们可以通过左右指针的状态，遍历出来每个高度下的最大接水宽度
能遍历的证明：
1.这种做法最终能将左右指针收敛于同一个位置
2.在收缩时，若移动较矮的指针，则可能下次min(left, right)>h；若移动较高的指针，则下次min(left, right)一定不可能>h (因为上次的最小值没有被换掉，所以min(left, right)只可能变小而不能变大)
3.从最外侧往里收缩的时候，只有两种方法，即收缩left, right中的较小值，或收缩它们的较大值
结合23可证明，新纪录new_h必须收缩小端才能做到，且一定会在两个边界处逐渐变大，不会有遗漏
再结合1可证明，new_h最终必然等于max(height)，即最终必然会遍历完所有柱子

得到最后的面积包括柱子本身，不要忘记减去所有柱子的面积sum(height)

### 代码

```python3
class Solution:
    def trap(self, height: List[int]) -> int:
        left, right = 0, len(height) - 1
        ds = 0
        h = 0
        while left <= right:
            if height[left] < height[right]:
                if height[left] > h:
                    ds += (height[left] - h) * (right - left + 1)
                    h = height[left]
                left += 1
            else:
                if height[right] > h:
                    ds += (height[right] - h) * (right - left + 1)
                    h = height[right]
                right -= 1
        return ds - sum(height)
        
```