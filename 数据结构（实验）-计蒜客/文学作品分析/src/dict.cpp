#include "dict.h"

int Dict::insert(const char *str) {
    
    h.insert(str);
    size+=1;
    return 0;
}

/*
 ==========================================================================
 =================Please Do Not Modify Functions Below=====================
 ========================请不要修改下列函数实现================================
 ==========================================================================
 */

Dict::Dict() {
    size = 0;
}

void Dict::print() const {
    for (int i = 0; i < h.get_size(); i++) {
        if (h.get_pair(i)->first.compare("#")) {
            std::cout << "[" << h.get_pair(i)->first << "]:[" << h.get_pair(i)->second << "]\n";
        }
    }
    std::cout << "\nTotal: " << size << " words.\n";
}
