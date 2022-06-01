/*
设计并实现游戏人物类和人物位置类
*/

//#include "pch.h"
#include <iostream>
#include <string>

using namespace std;

class Point2D;
class Creature;

struct Point2D
{
	int x;
	int y;	
};

class Creature
{
public:
	string name;
	int id;
	Point2D location;

	int putcreaturelocal()
	{
		cout << "(" << location.x <<", "<< location.y << ")";
		return 0;
	}
};

int main()
{
	string function;
	int creatureid,x,y;
	Creature creature[100];
	int allcreature = 0;
	
	do
	{
		cin >> function;
		if (function.compare("n") == 0)
		{
			cin >> creature[allcreature].name>>x>>y;
			creature[allcreature].location.x=x;
			creature[allcreature].location.y=y;
			allcreature++;
		}
		if (function.compare("s") == 0)
		{
			cin >> creatureid;
			cout << "No. " << creatureid << " creature " << creature[creatureid].name << " is at ";
			creature[creatureid].putcreaturelocal();
			cout << endl;
		}
		if (function.compare("a") == 0)
		{
			for (int i = 0; i < allcreature; i++)
			{
				cout << "No. " << i << " creature " << creature[i].name << " is at ";
				creature[i].putcreaturelocal();
				cout << endl;
			}
		}
		if (function.compare("m") == 0)
		{
			cin >> creatureid >> x >> y;
			creature[creatureid].location.x = x;
			creature[creatureid].location.y = y;

		}
		if (function.compare("e") == 0)
		{
			break;
		}
	} while (true);
	return 0;
}
