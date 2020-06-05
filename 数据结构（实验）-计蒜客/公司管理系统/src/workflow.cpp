#include "workflow.h"
#include "worker.h"
#include "vector.h"
#include <iostream>

Job::~Job() {
	//delete this;
	num_job--;
}

Workflow::Workflow() {
	head = NULL;
	tail = NULL;
	size = 0;
}

Workflow::~Workflow() {
	//head = NULL;
	//tail = NULL;
	//size = 0;
}

int Workflow::insert(Job *j) {
	if(j==NULL)return 1;
	if (tail == NULL)
	{
		head = j;
		tail = j;
		
	}
	Job *tmp = tail;
	tail->next = j;
	size += 1;
	tail = j;
	tail->prev = tmp;
    return 0;
}

int Workflow::swap(int original_index, int target_index) {
	if(original_index>=size || target_index>=size || original_index<0 || target_index<0)return 1;
	if(original_index==target_index)return 1;
	Job *tmp1, *tmp2, *tp;
	bool flag1, flag2;
	tmp1 = head;
	flag1 = false;
	tmp2 = head;
	flag2 = false;
	for (int i = 0; i < size; i++)
	{
		if (i != original_index && flag1==false)
			tmp1 = tmp1->next;
		else
			flag1 = true;
		if (i != target_index && flag2 == false)
			tmp2 = tmp2->next;
		else
			flag2 = true;
	}
	tp = head;

	for (int i = 0; i < size; i++)
	{		
		if (i == original_index)
		{

			tp->prev->next = tmp2;
			tp->next->prev = tmp2;
			
		}
		else if (i == target_index)
		{
			tp->prev->next = tmp1;
			tp->next->prev = tmp1;			
		}
		tp = tp->next;
	}
	Job *t1, *t2;
	t1 = tmp1->prev;
	t2 = tmp1->next;
	tmp1->prev = tmp2->prev;
	tmp1->next = tmp2->next;
	tmp2->prev = t1;
	tmp2->next = t2;
    return 0;
}

Job *Workflow::pop() {
	if(head==NULL)return NULL;
	head = head->next;
    return head->prev;
}

int Workflow::process(vector *l, int index) {
	if(index>=0 && index<size){
		if(l==NULL)return 1;
		if(l->get(0)==NULL)return 1;
		Job *tmp=head;
		for (int i = 0; i < size; i++)
		{
			if (i == index)
			{
				tmp->worker = l->get(0);
				l->remove(0);
			}
			tmp = tmp->next;
			if(tmp==NULL)return 1;
		}
			return 0;
		}
	else
		return 1;


}
/*预警：以下内容不许修改。*/
int Job::num_job = 0;   //Do not remove or modify this line.
//警告：你不可以改动这一行！
Job::Job() {               //警告：你不可以改动这个函数！
    id = num_job;
    num_job++;
    next = NULL;
    prev = NULL;
    worker = NULL;
}
int Workflow::print() {     //警告：你不可以改动这个函数！
    Job * curr = head;
    int i = 0;
    if (curr == NULL) {
        std::cout << "Empty Flow\n";
        return 0;
    }
    while (curr != NULL) {
        std::cout << "[" << i << "]";
        curr->print();
        i++;
        curr = curr->next;
    }
    return 0;
}
int Job::print() {
    std::cout << "job [" << this->id << "]\n";
    return 0;
}
