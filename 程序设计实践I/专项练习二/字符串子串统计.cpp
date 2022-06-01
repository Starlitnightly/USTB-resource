
// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//#include "pch.h"
#include <iostream>
#include"stdlib.h"
#include"string.h"

using namespace std;
int getastring(char *a);
int putanswer(int a);



int getastring(char *flagstring)//获取子串及子串的出现次数
{
	int flaglength, fatherlength, sonlength, count = 0;
	flaglength = strlen(flagstring);
	char* fatherstring = (char*)malloc(sizeof(char*) * flaglength);
	char* sonstring = (char*)malloc(sizeof(char*) * flaglength);
	int i = 0, j = 0;
	do
	{
		*(fatherstring + i) = *(flagstring + i);
		i++;
	} while (*(flagstring + i) != ' '); *(fatherstring + i) = '\0'; i++;
	do
	{
		*(sonstring + j) = *(flagstring + i);
		i++; j++;
	} while (*(flagstring + i) != '\0'); *(sonstring + j) = '\0';
	fatherlength = strlen(fatherstring);
	sonlength = strlen(sonstring);
	for (i = 0; i < fatherlength; i++)
	{
		int k = 0;//遍历每个字符串



		
		do
		{
			
			if (*(sonstring + k) == '\0' || *(fatherstring + i + k)=='\0')
			{
				break;
			}
			k++;
		} while (*(fatherstring + i + k) == *(sonstring + k));
		
		if (k == (sonlength))
		{
			count++;
		}


	}
	free(sonstring);
	free(fatherstring);
	return count;
}

int putanswer(int a)//输出答案
{
	std::cout << a << std::endl;
	return 0;
}
int main()
{
	int strLen = 5;
	char ch;
	char* str = (char*)malloc(sizeof(char*) * strLen);
	int count = 0;
	do
	{
		std::cin.get(ch);
		count++;
		if (count >= strLen)
		{
			str = (char*)realloc(str, sizeof(char*) * (++strLen));
		}
		*(str + count - 1) = ch;

	} while (ch != '\n');
	*(str + count-1) = '\0';//输入字符串
	putanswer(getastring(str));
	free(str);
	return 0;
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


