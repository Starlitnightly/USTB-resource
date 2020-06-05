#include "hashtable.h"

int main() {
    HashTable * h = new HashTable();
    for (int i = 0; i < 10; i ++) {
        Node tmp("test");
        h->insert(tmp);
        /*if (i != 0 && a != 2) {
            break;
        }*/
    }
    //Node t("test");
    //std::cout<<h->get_size()<<endl;
    //std::cout<<t.get_pair()->first<<std::endl;
    //std::cout<<t.get_pair()->second<<std::endl;
    //std::cout<<h->hash(t);
    for (int i = 0; i < h->get_size(); i++) {
        if (h->get_pair(i)->first.compare("#")) {
            std::cout << "[" << h->get_pair(i)->first << "]:[" << h->get_pair(i)->second << "]\n";
        }
    }
    delete h;
    return 0;
}
