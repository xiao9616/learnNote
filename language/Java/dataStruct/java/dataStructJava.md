# 数据结构

## 链表

### 206反转链表

```java
public ListNode reverseList(ListNode head) {
        ListNode cur=head,prev=null,next=null;
        while(cur!=null){
            next=cur.next;
            cur.next=prev;
            prev=cur;
            cur=next;
        }
        return prev;     
    }
```

```python
    def reverseList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """
        cur,prev=head,None
        while(cur):
            cur.next,prev,cur=prev,cur,cur.next
        retur
```

### **141判断链表是否回环**

```java
public boolean hasCycle(ListNode head) {
        ListNode fast=head,slow=head;
        while(fast!=null&&slow!=null&&fast.next!=null){
            fast=fast.next.next;
            slow=slow.next;
            if(fast==slow){
                return true;
            }
        }
        return false;
    }
```

```python
 def hasCycle(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """
        fast=slow=head
        while(fast and slow and fast.next):
            fast=fast.next.next
            slow=slow.next
            if fast==slow:
                return True
        return False
```

## 栈和队列

### 20有效的括号

```pyth
def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """
        stack=[]
        map={")":"(","]":"[","}":"{"}
        for c in s:
            if c=="(" or c=="[" or c=="{":
                stack.append(c)
            elif not stack or map[c]!=stack.pop():
                return False
        return not stack
```

```java

```

### 232用栈实现队列

```python
class MyQueue:

    def __init__(self):
        """
        Initialize your data structure here.
        """
        self.input = []
        self.output = []

    def push(self, x: int) -> None:
        """
        Push element x to the back of queue.
        """
        self.input.append(x)

    def pop(self) -> int:
        """
        Removes the element from in front of queue and returns that element.
        """
        if self.output:
            return self.output.pop()
        else:
            while self.input:
                self.output.append(self.input.pop())
            return self.output.pop()

    def peek(self) -> int:
        """
        Get the front element.
        """
        if self.output:
            return self.output[-1]
        else:
            while self.input:
                self.output.append(self.input.pop())
            return self.output[-1]

    def empty(self) -> bool:
        """
        Returns whether the queue is empty.
        """
        if self.input or self.output:
            return False
        else:
            return True
```

## Hash

### 242有效的字母异位词

```py
def isAnagram(self, s: str, t: str) -> bool:
        sDict, tDict = {}, {}
        for item in s:
            sDict[item] = sDict.get(item,0) + 1
        for item in t:
            tDict[item] = tDict.get(item,0) + 1
        return tDict == sDict
```



## 二叉树

节点类

```java
public class node {

    int value;

    node leftChild;

    node rightChild;

    public node(int value) {
        this.value = value;
    }

    public node(int value, node leftChild, node rightChild) {
        this.value = value;
        this.leftChild = leftChild;
        this.rightChild = rightChild;
    }

    @Override
    public String toString() {
        return "node{" +
                "value=" + value +
                ", leftChild=" + leftChild +
                ", rightChild=" + rightChild +
                '}';
    }
}
```

接口

```java
public interface BinaryTree {

    public boolean isEmpty();

    public int size(node root);

    public int getHeight(node root);

    public node findKey(int val, node root);

    public void preOrderTraverse(node root);

    public void inOrderTraverse(node root);

    public void postOrderTraverse(node root);

    public void preOrderByStack();

    public void inOrderByStack();

    public void postOrderByStack();

    public void levelOrderByStack();

    public void insert(int val, node root);

}
```

实现类

```java
package com.xiao;

import java.util.Deque;
import java.util.LinkedList;
import java.util.Queue;

public class listBinaryTree implements BinaryTree {

    public node root;

    public listBinaryTree(node root) {
        this.root = root;
    }

    @Override
    public boolean isEmpty() {
        return this.root == null;
    }

    @Override
    public int size(node root) {
        if (root == null) {
            return 0;
        } else {
            int nl = this.size(root.leftChild);
            int nr = this.size(root.rightChild);
            return nl + nr;
        }
    }

    @Override
    public int getHeight(node root) {
        if (root != null) {
            int nl = this.getHeight(root.leftChild);
            int nr = this.getHeight(root.rightChild);
            return nl > nr ? nl + 1 : nr + 1;
        } else {
            return 0;
        }

    }

    @Override
    public node findKey(int val, node root) {
        if (root == null) {
            return null;
        } else if (root.value == val) {
            return root;
        } else {
            node node1 = this.findKey(val, root.leftChild);
            node node2 = this.findKey(val, root.rightChild);
            if (node1 != null && node1.value == val) {
                return node1;
            } else if (node2 != null && node2.value == val) {
                return node2;
            } else {
                return null;
            }
        }
    }

    @Override
    public void preOrderTraverse(node root) {
        if (root != null) {
            System.out.print(root.value + "  ");
            this.preOrderTraverse(root.leftChild);
            this.preOrderTraverse(root.rightChild);
        }
    }

    @Override
    public void inOrderTraverse(node root) {
        if (root != null) {
            this.inOrderTraverse(root.leftChild);
            System.out.print(root.value + "  ");
            this.inOrderTraverse(root.rightChild);
        }
    }

    @Override
    public void postOrderTraverse(node root) {
        if (root != null) {
            this.postOrderTraverse(root.leftChild);
            this.postOrderTraverse(root.rightChild);
            System.out.print(root.value + "  ");
        }
    }

    @Override
    public void preOrderByStack() {

    }

    @Override
    public void inOrderByStack() {
        Deque<node> stack = new LinkedList<>();
        node current = root;
        while (current != null || !stack.isEmpty()) {
            while (current != null) {
                stack.push(current);
                current = current.leftChild;
            }
            if (!stack.isEmpty()) {
                current = stack.pop();
                System.out.println(current.value);
                current = current.rightChild;
            }
        }
    }

    @Override
    public void postOrderByStack() {

    }

    @Override
    public void insert(int val,node root) {
        if (root == null) {
            root = new node(val);
        } else {
            if (root.value == val) {
                return;
            }

            if (val < root.value) {
                if (root.leftChild == null) {
                    root.leftChild = new node(val);
                } else {
                    this.insert(val, root.leftChild);
                }
            } else {
                if (root.rightChild == null) {
                    root.rightChild = new node(val);
                } else {
                    this.insert(val,root.rightChild);
                }
            }
        }
    }

    @Override
    public void levelOrderByStack() {
        if (root == null) {
            return;
        }
        Queue<node> queue = new LinkedList<>();
        queue.add(root);
        while (queue.size() != 0) {
            int len = queue.size();
            for (int i = 0; i < len; i++) {
                node temp = queue.poll();
                System.out.println(temp.value);
                if (temp.leftChild != null) {
                    queue.add(temp.leftChild);
                }
                if (temp.rightChild != null) {
                    queue.add(temp.rightChild);
                }
            }
        }
    }
}

```

### BFS广度优先

使用队列

### DFS深度优先

使用栈

# 算法

## 递归&分治

## 贪心

## 动态规划

### 70. 爬楼梯

```pyth
def climbStairs(self, n: int) -> int:
        a,b=1,1
        for i in range(n):
            a,b=b,a+b
        return a
```

### 120. 三角形最小路径和

```cpp
int minimumTotal(vector<vector<int>>& triangle) {
        for(int i=triangle.size()-2;i>=0;--i){
            for(int j=0;j<triangle[i].size();j++)
                triangle[i][j]+=min(triangle[i+1][j],triangle[i+1][j+1]);
        } 
        return triangle[0][0];
    }
```

