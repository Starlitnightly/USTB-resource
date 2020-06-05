#include <string>
#include <iostream>
#include <stdio.h>
#include "suan_png.h"
#include "pxl.h"
#include "tree.h"

int test1(const char *input);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("./test [input image]\n");
        exit(1);
    }
    test1(argv[1]);
    return 0;
}

int test1(const char *input) {
    PNG *p = new PNG();
    std::string str = std::string(input);
    p->load(str);
    Tree *n = new Tree();
    n->load_png(p);
    n->judge(50);
    str = std::string("pic/output.png");
    p->save(str);
    delete n;
    delete p;
    return 0;
}
