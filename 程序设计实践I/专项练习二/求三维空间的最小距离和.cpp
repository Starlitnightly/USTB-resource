//#include "pch.h"
#include <iostream>
#include"stdlib.h"
#include"math.h"

int geteverytime(int local[3], int star[3])//计算目的地到一个星球的时间
{
	int x, y, z, x1, y1, z1, time;
	x = *local; y = *(local + 1); z = *(local + 2);
	x1 = *star; y1 = *(star + 1); z1 = *(star + 2);
	time = abs((x1 - x)) + abs((y - y1)) + abs((z - z1));
	return time;
}

int getminlocationtime(int a, int **b)//计算所花最小时间
{
	int local[3];//定义目的地数组
	int x1,y1,z1,x2,y2,z2,i,j,k,l;
	x1 = b[0][0]; y1 = b[0][1]; z1 = b[0][2];//找出最上方的星球-初始化
	x2 = b[0][0]; y2 = b[0][1]; z2 = b[0][2];//找出最下方的星球-初始化

	for (i = 0; i < a - 1; i++)
	{
		if (b[i + 1][0] >= b[i][0] && b[i + 1][1] >= b[i][1] && b[i + 1][2] >= b[i][2])
		{
			x1 = b[i + 1][0];
			y1 = b[i + 1][1];
			z1 = b[i + 1][2];
		}//找出最上方的星球
		
			
		if (b[i + 1][0] <= b[i][0] && b[i + 1][1] <= b[i][1] && b[i + 1][2] <= b[i][2])
		{
			x2 = b[i + 1][0];
			y2 = b[i + 1][1];
			z2 = b[i + 1][2];
		}//找出最下方的星球
	}
	

	int total1=0,total,tag1=0;
	bool op;
	for (i = x2;i <= x1; i++)
	{
		for (j = y2; j <= y1; j++)
		{
			for (k = z2; k <= z1; k++)
			{
				tag1++;//用于第一次判断
				
				op = false;
				local[0] = i; local[1] = j; local[2] = k;
				for (l = 0; l < a; l++)
				{
					if (i == b[l][0] || j == b[l][1] || k == b[l][2])
					{
						op = true;//判断是否至少有一个星球满足
						break;//有满足立刻跳出循环
					}	
				}
				if (op == false)
					continue;

				if (op == true)//条件满足时执行total计算
				{
					total1 = 0;
					for (l = 0; l < a; l++)
					{
						total1 += geteverytime(local, b[l]);
					}
					
				}
				
				if (tag1 == 1)total = total1;//total初始化

				if (op==true)//找到最小的total
				{
					if (total > total1)total = total1;
				}
				
				
			
			}
		}
	}

	return total;
}
int main()
{
	int **a;
	int len = 0, i;
	
	std::cin >> len;//输入星球个数
	a = (int **)malloc(len * sizeof(int *));
	for (i = 0; i < len; i++)
		a[i] = (int*)malloc(sizeof(int) * 3);//动态分配一个数组用于储存星球的xyz
	
	for (i = 0; i < len; i++)//输入星球的xyz
	{
		std::cin >> a[i][0];
		std::cin >> a[i][1];
		std::cin >> a[i][2];
		continue;
	}
	
	std::cout<< getminlocationtime(len, a)<<std::endl;//计算最短时间

	for (i = 0; i < len; i++)//释放动态数组
		free(a[i]);
	free(a);
}

