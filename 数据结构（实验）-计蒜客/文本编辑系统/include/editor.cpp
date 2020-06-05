#include "stack.h"
#include "queue.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

Stack<std::string> *history;

Stack<std::string> *tmp;


int resume();
int undo();


int resume() {
    if(tmp==NULL)
    {
        tmp=new Stack<std::string>();
        return 1;
    }

    if(tmp->get_size()!=0)
    {
        history->push(tmp->top());
        tmp->pop();
        return 2;
    }
    return 0;
}

int undo() {
    if(history==NULL)
    {
        history=new Stack<std::string>();
        return 1;
    }

    if(history->get_size()!=0)
    {
        Node<std::string> *tmp1=history->pop();
        if(tmp==NULL)
        {
            tmp=new Stack<std::string>();
            tmp->push(tmp1->ptr);
            return 2;
        }    
            tmp->push(tmp1->ptr);
            return 3;
    }
    return 0;
}
