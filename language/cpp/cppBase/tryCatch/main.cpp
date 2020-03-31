#include <iostream>
using namespace std;
double division(int a, int b)
{
    if( b == 0 )
    {
        throw "Division by zero condition!";
    }
    return (a/b);
}

class myException:public exception {
public:
    const char *what() const throw() {
        return "my exception";
    }

};
int main() {
    int x = 50;
    int y = 0;
    double z = 0;

    try {
        z = division(x, y);
        cout << z << endl;
    }catch (const char* msg) {
        cerr << msg << endl;
    }

    try{
        throw myException();
    } catch (exception &exception1) {
        cerr<<exception1.what()<<endl;
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}