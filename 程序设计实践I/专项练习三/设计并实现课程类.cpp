/*
设计并实现课程类
*/

//#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class Course//定义课程类
{
private:
	
public:
	int coursenum;//课程号
	string coursename;//课程名
	int courseforenum;//先修课的课程号
	Course() {};
	Course(string name, int forecourse)//构造函数
	{
		coursename = name;
		courseforenum = forecourse;
	}
	~Course() {};//析构函数

	int getcoursename(string name)//获得课程名
	{
		coursename = name;
		return 0;
	}
	int getcoursenum(int num)//获得课程号
	{
		coursenum=num;
		return 0;
	}
	int gercourseforenum(int num)//获得先修课的课程号
	{
		courseforenum = num;
		return 0;
	}
	int putcourseforenum()//输出先修课的课程号
	{
		return courseforenum;
	}
};

int main()
{
	Course school[255];//创建一个课程数组
	int allcourse = 0,coursefornum=-1;//定义课程总数=0，课程先修课默认-1
	string function;//定义接口
	string coursename;//定义课程名
	int coursenum, temporarynum=-1;
	do
	{
		
		cin>>function;
		if (function.compare("c") == 0)//接口为c时，为课程数组赋值
		{
			cin >> coursename >> coursefornum;
			school[allcourse].getcoursename(coursename);
			school[allcourse].gercourseforenum(coursefornum);
			school[allcourse].getcoursenum(allcourse++);
		}
		if (function.compare("s") == 0)//接口为s时，展示所有课程
		{
			
			for (int i = 0; i <= allcourse-1; i++)
			{
				cout << "Course " << i << "-" << school[i].coursename << " has prerequisites: ";
				if (school[i].courseforenum != -1)
				{
					temporarynum = school[i].putcourseforenum();
					do
					{
						cout << school[temporarynum].coursename<<" ";
						temporarynum = school[temporarynum].putcourseforenum();
					} while (temporarynum != -1);
					cout << endl;
				}
				else cout << "none"<<endl;
			}
			function = "y";
		}
		if (function.compare("e") == 0)//接口为e时，退出程序
		{
			break;
		}
	} while (true);
	
	return 0;
}

