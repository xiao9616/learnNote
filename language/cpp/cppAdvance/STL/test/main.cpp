#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <map>

using namespace std;
using namespace std::placeholders;

double myDivide(double x, double y){
    return x/y;
}


int func(int a, int b) {
    return a + 3 * (b - 1);
}

void forFun(int i) {
    cout << i << endl;
}

bool check(const int &i) {

    return i < 4;
}

bool sortRule(const int &i, const int &j) {
    return (i > j);
}



int main() {
    list<int> list1{1, 2, 3, 4, -9, -6};
    int init = 0;
    int result = accumulate(list1.begin(), list1.end(), init, func);
    cout << result << endl;

    for_each(list1.begin(), list1.end(), forFun);
    auto begin = list1.begin();
    auto end = list1.end();
    replace(begin, end, 1, 0);
    int n = count_if(begin, end, check);
    cout << n << endl;

    list1.sort(sortRule);
    for_each(list1.begin(), list1.end(), forFun);

    map<int, int> map1 = {{1, 10},
                          {2, 20},
                          {5, 50},
                          {4, 40}};
    map1.insert(pair<int, int>(-1, -10));
    for (auto &i:map1) {
        cout << i.first << i.second << endl;
    }
    vector<int> list2{1, 2, 3, 4, 5, 6};
    sort(list2.begin(), list2.end());
    cout << binary_search(list2.begin(), list2.end(), 4);


    cout<<"********************"<<endl;

    auto f = bind(myDivide, 10, 2);
    cout<<f()<<endl;
    auto fPlaceHolder=bind(myDivide,_1,2);
    cout<<f(10)<<endl;
    cout<<count_if(list2.cbegin(), list2.cend(), bind(less<int>(), _1, 3));

    return 0;
}