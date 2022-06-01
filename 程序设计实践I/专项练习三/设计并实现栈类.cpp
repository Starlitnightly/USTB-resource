/*
设计并实现栈类
*/

//#include "pch.h"
#include <iostream>
#include <string>
#include<cstdlib>

using namespace std;

class MyStack
{
private:
	int m_array[10];
	int m_size;

public:
	MyStack()
	{
		m_size = 0;
		for (int i = 0; i < 10; i++)
		{
			m_array[i] = 0;
		}
	}
	~MyStack() {};
	bool push(int stack)
	{
		if (m_size !=10)
		{
			m_array[m_size] = stack;
			m_size++;
			return true;
		}
		else 
		{ 
			return false;
		}

	}
	bool pop()
	{
		if (m_size !=0)
		{
			m_size--;
			m_array[m_size] = 0;
		}
		else
		{
			cout << "Can not pop empty stack";
			exit(0);
		}
	}
	int print()
	{
		cout << "( ";
		for (int i = 0; i < m_size; i++)
		{
			cout << m_array[i] <<" ";
		}
		cout << ")";
		return 0;
	}
};

int main()
{
	MyStack mystack;
	string function;
	int stack;
	do
	{
		cin >> function;//判断接口
		if (function.compare("i") == 0)
		{
			cin >> stack;
			mystack.push(stack);
		}
		if (function.compare("o") == 0)
		{
			mystack.pop();
		}
		if (function.compare("s") == 0)
		{
			mystack.print();
			break;
		}

	} while (true);
	return 0;
}
