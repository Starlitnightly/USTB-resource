//#include"pch.h"
#include<iostream>
#include"stdlib.h"

using namespace std;

int move(int *array, int n);


int main()
{
	int *a; int i = 0;
	int len = 5;
	a = (int*)malloc(sizeof(int*)*len);
	do
	{
		cin >> *(a + i);
		i++;
		if (i >= len)
			a = (int*)realloc(a, sizeof(int*)*(++len));
	} while (cin.get() != '\n');//输入不定长数组，回车结束
	move(a, i);

	free(a);
	return 0;
}

int move(int *array, int n)
{
	int x, y, z,i;
	x = array[n-3]; y = array[n-2]; z = array[n-1];
	for (i = n-1; i >= 3; i--)
	{
		array[i] = array[i - 3];
	}
	array[0] = x; array[1] = y; array[2] = z;
	for (i = 0; i < n; i++)
	{
		cout << array[i] << " ";

	}
	return 0;
}
