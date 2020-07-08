### 解题思路
方法一：单栈
1.用`pair`压栈两个数，一个是正常元素，另一个是目前最小值
方法二：双栈
1.一个栈正常压栈元素
2.另一个栈将最小值压栈
### 代码

```单栈 []
class MinStack {
public:
    stack<pair<int, int>> stk;
    MinStack() {

    }
    void push(int x) {
        if(stk.empty()) stk.push(make_pair(x, x)); //为空插入(x,x)
        else stk.push(make_pair(x, min(x, stk.top().second)));
    }
    void pop() {
        stk.pop();
    }
    int top() {
        return stk.top().first;
    }
    int getMin() {
        return stk.top().second;
    }
};
```
```双栈  []
class MinStack {
public:
    stack<int> stk, stkhelp;
    MinStack() {
        
    }
    void push(int x) {
        stk.push(x);
        if(stkhelp.empty()) stkhelp.push(x); //为空压入x
        else stkhelp.push(min(stkhelp.top(), x));
    }
    void pop() {
        stk.pop();
        stkhelp.pop();
    }
    int top() {
        return stk.top();   
    }
    int getMin() {
        return stkhelp.top();   
    }
};
```
