/*
设计并实现学生类和专业类
*/

//#include "pch.h"
#include<iostream>
#include<string>
#include <sstream>

using namespace std;

class Student;
class Major;

class Student
{
private:
	int studentnum;
	

public:
	string studentname;
	Student() {};
	Student(string name, int num)
	{
		studentname = name;
		studentnum = num;
	}
	~Student() {};
	int getstudentname(string name)
	{
		studentname = name;
		return 0;
	}
	int getstudentnum(int num)
	{
		studentnum = num;
		return 0;
	}
	int namegetnum(string name)
	{
		return studentnum;
	}
	
};

class Major
{
private:
	
	string majorid;
	

public:
	string majorname;
	string majorstu[50];
	int getmajorid(int id)
	{
		majorid = id;
		return 0;
	}
	int getmajorname(string name)
	{
		majorname = name;
		return 0;
	}
	int addstudent(int i, string name)
	{
		string con;
		stringstream con2;
		con2 << i;
		con2 >> con;
		majorstu[i] = con+"-"+name;
		return 0;
	}
	int delstudent(int i)
	{
		majorstu[i] = "";
		return 0;
	}
	


};
int main()
{
	Student student[100];
	Major major[100];
	int i, j;
	for (int k = 0; k < 100; k++)
	{
		for (int l = 0; l < 50; l++)
		{
			major[k].majorstu[l] = "";
		}
	}
	int stuid = 0,allstuid=0,majorid=0,allmajorid=0,foreid,nextid;
	string function;
	string stuname;
	string majname;
	do
	{
		cin >> function;
		if (function.compare("s") == 0)
		{
			
			cin>>stuname;
			student[allstuid].getstudentname(stuname);
			student[allstuid].getstudentnum(stuid);
			allstuid++;
			
		}
		if (function.compare("m") == 0)
		{
			
			cin >> majname;
			major[allmajorid].getmajorname(majname);
			major[allmajorid].getmajorid(majorid);
			allmajorid++;
		}
		if (function.compare("a") == 0)
		{
			cin>>stuid>>majorid;
			major[majorid].addstudent(stuid, student[stuid].studentname);
		}
		if (function.compare("d") == 0)
		{
			cin>>stuid>>majorid;
			major[majorid].delstudent(stuid);
		}
		if (function.compare("v") == 0)
		{
			cin >> foreid >>stuid>> nextid;
			major[foreid].delstudent(stuid);
			major[nextid].addstudent(stuid, student[stuid].studentname);

		}
		if (function.compare("n") == 0)
		{
			for (int i = 0; i < allstuid-1; i++)
			{
				cout << i << "-" << student[i].studentname << " ";
			};
			cout << allstuid-1 << "-" << student[allstuid-1].studentname;
			cout << endl;
		}
		if (function.compare("l") == 0)
		{
			for (int i = 0; i < allmajorid;i++)
			{
				cout << "Major " << i << "-" << major[i].majorname << ":";
				for (int j = 0; j < 50; j++)
				{
					if (major[i].majorstu[j] != "")
						cout <<" "<< major[i].majorstu[j];
				}
				cout << endl;
			}
		}
		if (function.compare("e") == 0)
		{
			break;
		}
	} while (true);
	return 0;
}

