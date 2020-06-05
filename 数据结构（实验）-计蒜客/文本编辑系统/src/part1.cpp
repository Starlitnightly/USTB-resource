#include <iostream>
#include "stack.h"
#include "queue.h"

int main() {
    Stack<int> *s = new Stack<int>();
    s->push(new int(1));
    s->push(new int(2));
    s->push(new int(3));
    s->print();
    Stack<int> *t = new Stack<int>(*s);
    delete s;
    t->push(new int(4));
    t->print();
    std::cout << "\n";
    delete t;
    return 0;
}