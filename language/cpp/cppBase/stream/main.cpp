#include <iostream>
#include <fstream>
using namespace std;

int main() {
    fstream file;
    file.open("/home/560204/LearnNote/C++高级/stream/note", ios::in);
    char content[100];
    while(file>>content)
    {
        cout<<content<<endl;
    }
    file.seekg(1,ios::end);
    file>>content;
    cout<<content<<endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}