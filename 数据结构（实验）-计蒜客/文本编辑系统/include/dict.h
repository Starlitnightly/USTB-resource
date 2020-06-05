#ifndef DICT_
#define DICT_

#include <iostream>
#include <string>
#include <utility>
#include "hashtable.h"

class Dict {
private:
    HashTable h;
    int size;
public:
    Dict();
    int insert(const char *str);
    void print() const;
};

#endif
