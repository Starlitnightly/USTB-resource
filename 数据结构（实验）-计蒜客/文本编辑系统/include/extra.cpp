#include <stack>
#include <queue>
int Compare_stack_queue(std::stack<int> *s, std::queue<int> *q);
void copy(std::stack<int> *s, std::queue<int> *q);
int compare(std::stack<int> *s, std::stack<int> *ss);

void copy(std::stack<int> *s, std::queue<int> *q)
{
    if(q->size()!=0)
    {
        s->push(q->front());
        q->pop();
        copy(s,q);
    }
}
int compare(std::stack<int> *s, std::stack<int> *ss)
{
    if(s->size()==ss->size() && ss->size()==0 )
        return 1;
    else if(s->top() != ss->top())
    return 0;
    else
    {
        s->pop();
        ss->pop();
        return compare(s,ss);
    }
}

int Compare_stack_queue(std::stack<int> *s, std::queue<int> *q) {
    if(q->size()!=s->size())return 0;
    std::stack<int> *tmp=new std::stack<int>();
    copy(tmp,q);
    return compare(s,tmp);
}
