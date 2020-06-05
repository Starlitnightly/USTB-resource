#include "queue.h"
#include <iostream>
template <class T>
Queue<T>::Queue() {
    head=NULL;
    tail=NULL;
    count=0;
}

template <class T>
Queue<T>::Queue(Queue &other) {
    count=other.count;
    if(other.head==NULL)
        head=new Node<T>();
    else
    {
        head=new Node<T>(*(other.head));
        copy(this->head,other.head);
        tail=head;
            while(tail->get_next())
                tail=tail->get_next();
    }
    
}

template <class T>
Queue<T>::~Queue() {
    remove(head);
}

template <class T>
Queue<T> &Queue<T>::operator=(Queue &other) {
    count=other.count;
    if(other.head==NULL)
        head=new Node<T>();
    else
    {
        head=new Node<T>(*(other.head));
        copy(this->head,other.head);
        tail=head;
            while(tail->get_next())
                tail=tail->get_next();
    }
    return *this;
}

template <class T>
int Queue<T>::get_size() const {
    
    return count;
}

template <class T>
void Queue<T>::push(T *t) {
    if(t==NULL)return;

    if(head==NULL)
        head=tail=new Node<T>(t);
    else
    {
        Node<T> *newnode=new Node<T>(t);
        tail->set_next(newnode);
        tail=newnode;
    }
    count++;
    return;
    
}

template <class T>
void Queue<T>::push(Node<T> *n) {
    if(n==NULL)return;
    if(count==0)
        head=tail=n;
    else
    {
        tail->set_next(n);
        tail=n;
    }
    count++;
    return;
    
}

template <class T>
Node<T> *Queue<T>::pop() {
    if(count>0)
    {
        Node<T> *tmp= head;
        head=head->get_next();
        count--;
        return tmp;
    }else
        return NULL;
}

template <class T>
void Queue<T>::print() {
    Node<T> *p = head;
    Stack<T> *stack=new Stack<T>();      
    while(p != NULL) {
        //p->print();
        stack->push(p->ptr);
        p = p->get_next();
    }
    stack->print();
    std::cout<<"END\n";

    return;
}

template <class T>
void Queue<T>::copy(Node<T> *this_, Node<T> *other_) {
    if (other_->get_next() == NULL) {
        return;
    }
    this_->set_next(new Node<T>(*(other_->get_next())));
    copy(this_->get_next(), other_->get_next());
    return;
}

template <class T>
void Queue<T>::remove(Node<T> *n) {
    if (n == NULL) {
        return;
    }
    if (n->get_next() == NULL) {
        delete n;
        return;
    }
    Node<T> *tmp = n->get_next();
    delete n;
    remove(tmp);
    return;
}
