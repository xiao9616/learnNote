#include <iostream>
using namespace std;

int main() {
    int i = 0;
    int *p = &i; //指针的使用
    cout << p << endl;
    cout << *p << endl;
    p = NULL;   //空指针
    if (!p)
        cout << p << endl;
    int value[3] = {1, 2, 3};//指针指向数组
    p = value;
    cout << *(++p) << endl;
    cout << *value << endl;//数组表示常指针，不可修改，所以不能使用value++
    int var[3] = {10, 100, 200};
    int *ptr[3];  //指针数组

    for (int i = 0; i < 3; i++) {
        ptr[i] = &var[i];
    }
    for (int i = 0; i < 3; i++) {
        cout << "Value of i1[" << i << "] = ";
        cout << *ptr[i] << endl;
    }

    int i1;
    int *ptr1;
    int **pptr;//指向指针的指针

    i1 = 3000;
    ptr1 = &i1;
    pptr = &ptr1;

    cout << "Value of i1 :" << i1 << endl;
    cout << "Value available at *ptr1 :" << *ptr1 << endl;
    cout << "Value available at **pptr :" << **pptr << endl;

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

//引用很容易与指针混淆，它们之间有三个主要的不同：
//不存在空引用。引用必须连接到一块合法的内存。
//一旦引用被初始化为一个对象，就不能被指向到另一个对象。指针可以在任何时候指向到另一个对象。
//引用必须在创建时被初始化。指针可以在任何时间被初始化。