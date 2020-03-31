#include <iostream>
#include <bitset>
#include <vector>

using namespace std;
void myprint(){

}

template<typename T, typename...Types>//特化版本
void myprint(const T &first, const Types &... args){
    cout<<first<<endl;
    cout<<sizeof...(args)<<endl;
    myprint(args...);
}

template<typename...Types>//泛化版本，有特化版本存在，泛化版本不会被调用
void myprint(const Types&... args){
    cout<<"泛化版本"<<endl;
}
int main() {
    myprint(2, "hihao", bitset<16>(789));
    std::cout << "Hello, World!" << std::endl;
    return 0;
}