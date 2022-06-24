#include "heap.h"

int main() {
    Heap *h = new Heap();
    for (int i = 0; i < 20; i++) {
        std::string str("asd");
        Player_info p(str, i, i * 2);
        h->insert(p);
    }
    h->print();
    delete h;
    return 0;
}
