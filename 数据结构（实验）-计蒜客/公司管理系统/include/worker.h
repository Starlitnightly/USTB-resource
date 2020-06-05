/*
 @file /include/worker.h
 */
#ifndef WORKER_H_
#define WORKER_H_
#include <string>

class Worker {
    /*
     This is a basic example of how class works in C++.
     It is designed to test if you know basic syntax of C++.
     这是一个很简单的 class，设计这部分的目的是检测你是否熟悉 C++ 基本语法.
     */
private:
    int id;                               // unique id for each worker, aka Team in Huayeke
    std::string name;                   // name of the worker
public:
    static int num_worker;              // keep track of the num of workers in action
    Worker();                          // default constructor
    ~Worker();                        // destructor
    Worker(std::string &input_name); // TODO
    int get_id();                   // TODO
    std::string &get_name();       // TODO
    int print();                  // print function
};

#endif
