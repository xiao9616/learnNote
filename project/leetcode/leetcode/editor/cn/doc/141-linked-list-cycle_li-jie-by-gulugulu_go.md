**法一：借助辅助空间**
```python3
class Solution:
    def hasCycle(self, head: ListNode) -> bool:
        a = set() 
        while head:
            
            if head in a:
                return True

            a.add(head)
            head = head.next
        return False
```
理解：   用一个set数据结构存储每个节点地址;
        时间复杂度O(n*1)：访问每个节点O(n)+存储每个节点O(1); 
        空间复杂度O(n)


**法二： 快慢指针法**
```python3
class Solution:
    def hasCycle(self, head: ListNode) -> bool:
        slow = fast = head
        # if not head：  # 没必要这样写可以加入while循环判断更简洁
        #     return False

        while fast and fast.next:  # 防止head为空和出现空指针的next的情况
            slow = slow.next
            fast = fast.next.next
            if slow is fast:
                return True

        return False
```
理解：
    思路：定义一个快指针和慢指针,每次快指针走2步，慢指针走1步，判断快指针是否与慢指针重逢
    时间复杂度O(n+k)：
        情况一：链表部分成环O(n)；
            部分成环时，快指针先于慢指针进入环，慢指针进环时间O(n)；当快慢指针都进入环，假设环节点数量为K,当快慢指针第一次相遇时，快指针至少已经在环内已经比慢指针多走一圈(多走的这一圈是当慢指针进入后开始算的)，时间O(k)； 综上，时间复杂度O(k+n)，即为O(n)

        情况二：链表完全成环O(n)
            同起点，第一次相遇时，快指针已经在环内已经比慢指针多走一圈；时间复杂度O(n)


**法三：递归标记法**
```python3
class Solution:
    def hasCycle(self, head: ListNode) -> bool:
        if not head:
            return False

        if head == 0xcafebabe:
            return True

        head.val = 0xcafebabe
        return self.hasCycle(head.next)

)
```
理解：
    思路：把访问过的值都进行赋值，如果链表完全成环，则必会出现重复值
    时间复杂度：O(n);访问O(n)+赋值O(1)
    空间复杂度：O(1)
