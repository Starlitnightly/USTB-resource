/*
 @file /include/workflow.h
 */
#ifndef WORKFLOW_H
#define WORKFLOW_H
#include <memory>
#include "worker.h"
#include "vector.h"

class Job {
private:
    static int num_job;
    int id;
public:
    Worker *worker;
    Job *next;
    Job *prev;
    Job();
    ~Job();                                           //TODO
    int print();
};

class Workflow {
private:
    Job *head;
    Job *tail;
    int size;
public:
    Workflow();                                       //TODO
    ~Workflow();                                      //TODO
    int insert(Job *j);                               //TODO
    int swap(int original_index, int target_index);   //TODO
    Job *pop();                                       //TODO
    int process(vector *l, int index);                //TODO
    int print();
};
#endif
