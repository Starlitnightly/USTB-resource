#include <iostream>
#include <string>
#include <csignal>
#include "vector.h"
using namespace std;
int test1(int i);
int test2(int i);
int test3(int i);

void signalHandler( int signum ) {
    cout << "\nSegmentation Fault.\n";
    exit(signum);
}

int main() {
    signal(SIGABRT, signalHandler);
    test1(1);
    test2(2);
    test3(3);
    return 1;
}

int test1(int i) {
    cout << "任务1 单元测试" << i << "\n";
    Worker *blah = new Worker();
    blah->print();
    string tmp = string("Blah2");
    Worker *blah2 = new Worker(tmp);
    blah2->print();
    delete blah;
    delete blah2;
    return 0;
}

int test2(int i) {
    cout << "任务1 单元测试" << i << "\n";
    vector *JSK = new vector(3);
    for (int i = 0; i < 30; i++) {
        string tmp = string("单元测试");
        Worker *RnD = new Worker(tmp);
        JSK->insert(RnD);
    }
    JSK->print();
    delete JSK;
    return 0;
}

int test3(int i) {
    cout << "任务1 单元测试" << i << "\n";
    vector *JSK = new vector(3);
    for (int i = 0; i < 30; i++) {
        string tmp = string("RnD");
        Worker *RnD = new Worker(tmp);
        JSK->insert(RnD);
        //JSK->print();
    }
    for (int i = 0; i < 21; i += 10) {
        JSK->get(i)->print();
    }
    JSK->remove(20);
    JSK->print();
    delete JSK;
    return 0;
}
