#include <iostream>
#define LENGTH 10;
using namespace std;

typedef int xiao;
enum color {
    red, black, green
};
int k;//当局部变量被定义时，系统不会对其初始化，您必须自行对其初始化。定义全局变量时，系统会自动初始化
static int count = 10; /* 全局变量 当 static 修饰全局变量时，会使变量的作用域限制在声明它的文件内。 */
extern i;//extern 是用来在另一个文件中声明一个全局变量或函数。
int main() {
    xiao i = 1;
    color j = red;
    cout << i << endl;
    cout << j << endl;

    cout << k << endl;
    cout << LENGTH;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}