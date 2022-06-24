#include "heap.h"
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

#define USR_THRESHOLD 150

Player_info *get_info();

Player_info *get_info() {
    char * buffer = NULL;
    size_t s;
    if (getline(&buffer, &s, stdin)) {
        //printf("%s", buffer);
        char *usr = (char*)calloc(1,64);
        long uid;
        int score;
        int index = 0;
        while (1) {
            char blah[2];
            blah[0] = *(buffer + index);
            blah[1] = '\0';
            index++;
            if (blah[0] != ' ') {
                strcat(usr, blah);
            }
            else {
                break;
            }
        }
        sscanf(buffer + index, "%ld %d\n", &uid, &score);

        std::string s = std::string(usr);

        Player_info *ret = new Player_info(s, uid, score);
        free(usr);
        free(buffer);
        return ret;
    }
    return NULL;
}

int main() {
    Heap *h = new Heap();
    printf("Please Enter Following Info: [Username] [uid] [score]\n");
    for (int i = 0; i < 200000; i++) {
        Player_info *p = get_info();
        h->insert(*p);
        delete p;
    }
    Player_info *vec = h->sort();
    for (int i = 0; i < 2000; i++) {
        vec[i].print();
    }
    delete[] vec;
    delete h;
    return 0;
}
