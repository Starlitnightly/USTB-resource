#include "stack.h"
#include <iostream>

template <class T>
Node<T>::Node() {
    ptr = NULL;
    next = NULL;
}

template <class T>
Node<T>::Node(Node<T> & other) {
    next = NULL;
    ptr = new T(*(other.ptr));
}

template <class T>
Node<T> & Node<T>::operator=(Node<T> & other) {
    next = NULL;
    ptr = new T(*(other.ptr));
    return *this;
}

template <class T>
Node<T>::Node(T *t) {
    ptr = t;
    next = NULL;
}

template <class T>
Node<T>::~Node() {
    if(ptr != NULL) {
        delete ptr;
    }
}

template <class T>
Node<T> *Node<T>::get_next() const {
    return next;
}

template <class T>
void Node<T>::set_next(Node<T> * n) {
    next = n;
    return;
}

template <class T>
void Node<T>::print() {
    std::cout << "[" << *ptr << "]->";
    return;
}

/*
The whole stack was essentially a singlely linked list.
The 'Top' Node is actually
the head of the linked list.
*/

template <class T>
Stack<T>::Stack() {
    length = 0;
    top_ = NULL;
}

template <class T>
Stack<T>::Stack(Stack<T>& other) {
    length = other.length;
    if (other.top_ == NULL) {
        top_ = new Node<T>();
    } else {
        top_ = new Node<T>(*(other.top_));
        copy(this->top_, other.top_);
    }

}

template <class T>
Stack<T> & Stack<T>::operator=(Stack<T> & other) {
    length = other.length;
    if (other.top_ == NULL) {
        top_ = new Node<T>();
    } else {
        top_ = new Node<T>(*(other.top_));
        copy(this->top_, other.top_);
    }
    return *this;
}

template <class T>
Stack<T>::~Stack() {
    remove(top_);
}

template <class T>
T *Stack<T>::top() {
    if (top_ != NULL)
		{
			//top_->print();
			return top_->ptr;
		}
		else
			return NULL;
}

template <class T>
void Stack<T>::push(T *t) {
    if(t==NULL)return;
    Node<T> *tmp = new Node<T>(t);
    if(length>0)
    {
        tmp->set_next(top_);
        top_ = tmp;
        length++;
    }
    else
    {
        top_=tmp;
        length++;
    }
    
    return;
}

template <class T>
void Stack<T>::push(Node<T> *n) {
	
    if(n==NULL)
        return;
    Node<T> *tmp= new Node<T>(*n);
    if(length>0)
    {
        tmp->set_next(top_);
        top_=tmp;
	    length++;
    }
    else
    {
        top_=tmp;
	    length++;
    }
    
	return;
}

template <class T>
Node<T> *Stack<T>::pop() {
		if (length>0)
		{
			Node<T> *tmp = top_;
			top_ = top_->get_next();
            length--;
			return tmp;

		}
		else
			return NULL;
}

template <class T>
int Stack<T>::get_size() const {
    return length;
}

template <class T>
void Stack<T>::print() const {
    Node<T> *p = top_;
    while(p != NULL) {
        p->print();
        p = p->get_next();
    }
    return;
}

template <class T>
void Stack<T>::copy(Node<T> *this_, Node<T> *other_) {
    if (other_->get_next() == NULL) {
        return;
    }
    this_->set_next(new Node<T>(*(other_->get_next())));
    copy(this_->get_next(), other_->get_next());
    return;
}

template <class T>
void Stack<T>::remove(Node<T> *n) {
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
