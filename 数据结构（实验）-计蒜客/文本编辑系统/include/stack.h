#ifndef STACK_H_
#define STACK_H_
#include <iostream>

template <class T>
class Node {
public:
    Node();
    Node(Node & other);
    Node & operator=(Node & other);
    Node(T *t);
    ~Node();
    Node *get_next() const;
    void set_next(Node *n);
    void print();
    T *ptr;
private:
    Node *next;
    
};

template <class T>
class Stack {
public:
    Stack();
    Stack(Stack & other);
    Stack & operator=(Stack & other);
    ~Stack();
    T *top();
    void push(T *t);
    void push(Node<T> *n);
    Node<T> *pop();
    int get_size() const;
    void print() const;
private:
    void copy(Node<T> *this_, Node<T> *other_);
    void remove(Node<T> *n);
    int length;
    Node<T> *top_;
};
#include "stack.cpp"
#endif
