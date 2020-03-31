#include <iostream>
#include <string>
#include <list>
using namespace std;
class Component{
public:
    virtual void process()=0;

    virtual ~Component() {

    }
};

class Composite:public Component {
    string name;
    list<Component*> elements;
public:
    Composite(const string &name) : name(name) {}

    void add(Component *element){
        elements.push_back(element);
    }

    void remove(Component *element){
        elements.remove(element);
    }

    void process() override {
        cout << name << endl;
        for (auto &e:elements) {
            e->process();
        }
    }
};

class Leaf:public Component {
    string name;
public:
    Leaf(const string &name) : name(name) {}

    void process() override {
        cout << "i am leaf " << name << endl;
    }
};
int main() {
    Composite root("root");
    Composite treeNode1("treeNode1");
    Composite treeNode2("treeNode2");
    Composite treeNode3("treeNode3");
    Composite treeNode4("treeNode4");
    Leaf leaf1("left1");
    Leaf leaf2("left2");

    root.add(&treeNode1);
    treeNode1.add(&treeNode2);
    treeNode2.add(&leaf1);

    root.add(&treeNode3);
    treeNode3.add(&treeNode4);
    treeNode4.add(&leaf2);

    root.process();
    return 0;
}