#include "hashtable.h"
#include "dict.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

int read_from_file(FILE * input_file, Dict *d);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        exit(1);
    }
    FILE *input = fopen(argv[1], "r");
    if (input == 0) {
        perror("Fopen Failed ");
        exit(-1);
    }
    Dict d = Dict();
    read_from_file(input, &d);
    fclose(input);
    d.print();
    return 0;
}

int read_from_file(FILE * input_file, Dict *d) {
    bool flag;
    flag=false;
    char *str=new char[20];
    int n=0;
    char c;
    while((c=fgetc(input_file))!=EOF)
    {
        if(isalpha(c))
        {
            str[n++]=tolower(c);
            flag=true;
        }
        else
        {
            if(flag){
                //cout<<str<<endl;
                str[n]='\0';
                d->insert(str);
                n=0;
                flag=false;
            }
        }
        
            
    }
    
    
    return 0;
}
