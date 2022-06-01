/*
ÉßĞÎ¾ØÕó
*/

//#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int moveadd(int origin, int pace)
{
	return origin + pace;
}
int moveminus(int origin, int pace)
{
	return origin -pace;
}
int main()
{
	int n;
	cin >> n;
	int **array;
	array = new int*[n];
	for (int i = 0; i < n; i++)
		array[i] = new int[n];
	int line1 = n / 2 ;
	int row1 = n / 2 ; 
	int pace = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			array[i][j] = 0;
		}
	}
	array[line1][row1] = 1;
	int way = 1,pacemid=0;
	
	for (int i = 1; i < n*n; i++)
	{
		
		
		if (way == 1)
		{
			row1 ++;
			array[line1][row1] = (i + 1);
			if (array[line1][row1-1] != 0 && array[line1-1][row1] == 0)
				way=2;
		}else if (way == 2)
			{
				line1--;
				array[line1][row1] = (i+1);
				pace++;
				if (array[line1+1][row1] != 0 && array[line1][row1-1] == 0)
					way=3;
			}else if (way == 3)
				{
					row1--;
					array[line1][row1] = (i + 1);
					pace++;
					if (array[line1][row1+1] != 0 && array[line1+1][row1] == 0)
						way=4;
				}else if (way == 4)
					{
						line1++;
						array[line1][row1] = (i + 1);
						pace++;
						if (array[line1-1][row1] != 0 && array[line1][row1+1] == 0)
							way=1;
					}
			
		
		

	}
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		max += array[i][i];
		max += array[i][n - i-1];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << array[i][j]<<" ";
		}
		cout << endl;
	}
	cout << max-1;
	for (int i = 0; i < n; i++)
		delete[]array[i];
	delete[]array;

}
