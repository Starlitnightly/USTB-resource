/*
 @file /include/vector.h
 */
#ifndef vector_H
#define vector_H
#include "worker.h"

class vector {
    //This is a class of vector. As you can see it is actually a vector of workers.
    /*这是 vector 类，你也许已经发现了，它其实是一个 Worker 的线性表*/
private:
    int size;  // vector 的容量
    int length;  // vector 中的元素个数
    Worker **data;
    /*
     提示：这里的 data 是一个指向指针的指针。
     在操作指针前请三思！
     */
public:
    vector(int input_size);
    ~vector();                          //TODO
    int insert(Worker *new_worker);   //TODO
    Worker *remove(int index);        //TODO
    void expand();
    Worker *get(int index);           //TODO
    void print();
};

#endif
