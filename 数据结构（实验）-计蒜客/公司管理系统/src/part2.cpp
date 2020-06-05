#include <iostream>
#include <string>
#include <csignal>
#include "workflow.h"
using namespace std;

int test1(int i);

int test2(int i);

void signalHandler( int signum ) {
    cout << "\nSegmentation Fault.\n";
    exit(signum);
}

int main() {
    signal(SIGABRT, signalHandler);
    test1(1);
    test2(2);
    return 0;
}

int test1(int i) {
    cout << "任务2 单元测试" << i << "\n";
    Workflow *flow = new Workflow();
    for (int i = 0; i < 20; i++) {
        flow->insert(new Job());
    }
    flow->swap(4, 10);
    flow->print();

    delete flow;
    return 0;
}

int test2(int i) {
    cout << "任务2 单元测试" << i << "\n";
    Workflow *flow = new Workflow();
    vector *v = new vector(10);
    for (int i = 0; i < 12; i++) {
        v->insert(new Worker());
    }
    for (int i = 0; i < 20; i++) {
        flow->insert(new Job());
    }
    flow->print();
    delete flow;
    delete v;
    return 0;
}
