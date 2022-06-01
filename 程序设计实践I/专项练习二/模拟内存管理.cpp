//#include"pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
using namespace std;

struct memNode {
	int start;  //内存块起始位置
	int end;  //内存块终止位置（包含）
	int hand; //句柄号
	bool operator<(memNode &b)
	{
		return start < b.start;
	}
};

list<memNode> empty;//空的内存块链表
list<memNode> used; //已分配内存链表
int MaxMem;
int handle = 0;

int mynew(int maxsize, int size)
{
	//在空闲链表中寻找可用内存块
	for (list<memNode>::iterator i = empty.begin(); i != empty.end(); i++)
	{
		if (i->end - i->start + 1 > size)//若该空闲块大于所需内存，将该块分割，被分配的部分加入used，更新该块剩下空闲的起始位置
		{
			handle++;
			memNode m;
			m.start = i->start;
			m.end = i->start + size - 1;
			m.hand = handle;
			used.push_back(m);
			i->start = i->start + size;
			return handle;
		}
		else if (i->end - i->start + 1 == size)//若该空闲块等于所需内存，将该块加入used，从empty中删去该块
		{
			handle++;
			memNode m;
			m.start = i->start;
			m.end = i->end;
			m.hand = handle;
			used.push_back(m);
			empty.erase(i);
			return handle;
		}
	}
	return false;  //找不到合适的空闲块则分配失败
}
bool del(int handle)//释放内存块
{
	bool res = false;
	for (list<memNode>::iterator i = used.begin(); i != used.end(); i++) //根据句柄在used中查找内存
	{
		if (i->hand == handle)
		{
			res = true;
			for (list<memNode>::iterator ie = empty.begin(); ie != empty.end(); ie++)//因为要将该块返回到空闲内存链表中，同时每次分配空闲块时需要小地址优先，所以要寻找合适的插入位置，并在used中删除该块
			{
				//若该块正好可以与empty中的某个空闲块首尾相连，则更新empty中该空闲块的起始或终止位置
				if (ie->end + 1 == i->start)
				{
					ie->end = i->end;
					used.erase(i);
					return true;
				}
				if (i->end + 1 == ie->start)
				{
					ie->start = i->start;
					used.erase(i);
					return true;
				}
				//找到第一个起始地址大于该释放内存块的终止地址的空闲块，将该块插入到其前面。
				if (i->end + 1 < ie->start)
				{
					memNode m;
					m.start = i->start;
					m.end = i->end;
					m.hand = 0;
					used.erase(i);
					empty.insert(ie, m);
					return true;
				}
			}
			//若不符合上面情况，直接在empty末尾插入
			memNode m;
			m.start = i->start;
			m.end = i->end;
			m.hand = 0;
			empty.push_back(m);
			used.erase(i);
			return true;
		}
	}
	return res;
}
void def()
{
	used.sort();//需要从低地址开始迁移，所以先对used进行排序
	int count = 1;//记录当前used已使用到的位置
	for (list<memNode>::iterator i = used.begin(); i != used.end(); i++)//更新used中内存块的地址，即向低地址端迁移
	{
		i->end = i->end - i->start + count;
		i->start = count;
		count = i->end + 1;
	}
	//empty中所有空闲块合并，所以将其清空，插入count到最大内存地址的地址块
	empty.clear();
	memNode m;
	m.start = count;
	m.end = MaxMem;
	m.hand = 0;
	empty.push_back(m);
}
int main()
{
	int T;
	cin >> T >> MaxMem;
	memNode m;
	m.start = 1;
	m.end = MaxMem;
	empty.push_back(m);
	for (int i = 0; i < T; i++)
	{
		string order;
		int size;
		cin >> order;
		if (order.compare("new") == 0)
		{
			cin >> size;
			int res = mynew(MaxMem, size);
			if (res == 0)
				cout << "NULL" << endl;
			else
				cout << res << endl;
		}
		else if (order.compare("del") == 0)
		{
			cin >> size;
			bool res = del(size);
			if (!res)
				cout << "ILLEGAL_OPERATION" << endl;
		}
		else if (order.compare("def") == 0)
			def();
	}
	return 0;
}

