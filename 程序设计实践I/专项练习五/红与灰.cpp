/*
红与灰
*/

//#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	int m, n;
	cin >> m >> n;//n行m列
	
	/*
	动态分配二维数组
	*/
	char **gamemap,**recordmap;
	gamemap = new char*[n];
	recordmap = new char*[n];
	for (int i = 0; i <  n; i++)
	{
		gamemap[i] = new char[m];
		recordmap[i] = new char[m];
	}

	//输入地图及记录地图
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> gamemap[i][j];
			recordmap[i][j] = 0;
			if (gamemap[i][j] == '@')
			{
				recordmap[i][j] = 1;
			}
			
		}
	}
	
	/*
	思路：
		循环扫描地图，初始化人(@)的位置,在记录地图上为1
		第一次扫描地图，如果在记录地图上发现1，那么在游戏地图的对应位置扫描附近的四个格子
		如果有灰色格子(.),那么在记录地图上将这些灰色格子的位置都标记1
		第二次扫描地图，还是找到1就在游戏地图上判断附近的灰色格子，有就标记为1；
		……
		直到n*m次扫描结束，玩家所能到达的所有位置都已成功标记为1.
	*/
	for (int k = 0; k < n*m; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (recordmap[i][j] == 1)
				{
					if (i - 1 >= 0)
					{
						if (gamemap[i - 1][j] == '.')
							recordmap[i - 1][j] = 1;
					}
					if (i + 1 < n)
					{
						if (gamemap[i + 1][j] == '.')
							recordmap[i + 1][j] = 1;
					}
					if (j - 1 >= 0)
					{
						if (gamemap[i][j - 1] == '.')
							recordmap[i][j - 1] = 1;
					}

					if (j + 1 < m)
					{
						if (gamemap[i][j + 1] == '.')
							recordmap[i][j + 1] = 1;
					}
				}

			}
		}

	}
	//记录1的个数
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (recordmap[i][j] == 1)
			{
				max++;
			}

		}
	}

	//输出1个个数
	cout << max;


	/*
	释放二维数组
	*/
	for (int i = 0; i < n; i++)
	{
		delete[]gamemap[i];
		delete[]recordmap[i];
	}
	delete[]gamemap;
	delete[]recordmap;
	return 0;
}

