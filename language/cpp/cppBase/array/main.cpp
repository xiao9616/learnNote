#include <iostream>
using namespace std;

int main() {
    int n[ 10 ]; // n 是一个包含 10 个整数的数组

    // 初始化数组元素
    for ( int i = 0; i < 10; i++ )
    {
        n[ i ] = i + 100;
    }

    int a[3][4] = { //二维数组
            {0, 1, 2, 3} ,   /*  初始化索引号为 0 的行 */
            {4, 5, 6, 7} ,   /*  初始化索引号为 1 的行 */
            {8, 9, 10, 11}   /*  初始化索引号为 2 的行 */
    };
    cout<<*a[1]<<endl;

//    void myFunction(int *param)//形式参数是一个指针：
//    {
//        .
//        .
//        .
//    }
//
//    void myFunction(int param[10])//形式参数是一个已定义大小的数组：
//    {
//        .
//        .
//        .
//    }
//    void myFunction(int param[])//形式参数是一个未定义大小的数组
//    {
//        .
//        .
//        .
//    }

//    int * myFunction()//从函数返回一个一维数组，您必须声明一个返回指针的函数
//    {
//        .
//        .
//        .
//    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}