#include <iostream>
#include "stack.h"
#include "queue.h"

int main() {
    Queue<int> *q = new Queue<int>();
    q->push(new int(1));
    q->push(new int(2));
    q->push(new int(3));
    q->push(new int(4));
    //q->print();
    delete q->pop();
    q->push(new int(0xdeadbeef));
    q->print();
    delete q;
    return 0;
}
