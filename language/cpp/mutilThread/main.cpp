#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <condition_variable>
#include <future>

using namespace std;

mutex mutex1;
condition_variable con;

//void shared_print(string msg, int id){
//    lock_guard<mutex> locker(mutex1);
//    cout << msg << id << endl;
//}
//
//void function_1(){
//    for (int i = 0; i < 100; ++i) {
//        std::cout << "Hello, i am function" << i << std::endl;
//    }
//}
//
//class cla{
//public:
//    void operator()(string msg){
//        for (int i = 0; i < 100; ++i) {
//            std::cout << msg << "i am cla" << i << std::endl;
//        }
//    }
//};

int factorial(int N){
    int res=1;
    for (int i = N; i > 1; --i) {
        res*=i;
    }
    cout << "result is:" << res << endl;
    return res;
}

int main() {
//    string msg = "i love you";
//    cout << this_thread::get_id() << endl;
//    thread t1(function_1);
//    thread t2(cla(), move(msg));
//    thread t3 = move(t1);
//    cout << t2.get_id() << endl;
//    t2.join();
//    t3.join();
//    promise<int> p;
//    future<int> f=p.get_future();
//    future<int> fu = async(factorial, 10,ref(f));
//    int x=fu.get();
    packaged_task<int()> t(bind(factorial, 6));

    cout<<x;

    return 0;
}