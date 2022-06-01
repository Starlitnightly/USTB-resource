/*
设计并实现扫描仪类，打印机类和一体机类
*/

//#include"pch.h"
#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;

class PoweredDevice;
class Scanner;
class Printer;
class Copier;

class PoweredDevice
{
public:
	int Deviceamount=0;
	int stru[50];
	
};

class Scanner : public PoweredDevice
{
private:
	int amount=0;
public:
	int scanneramount;
	Scanner()
	{
		scanneramount = 0;
	}
	int createscanner()
	{
		stru[Deviceamount] = 0;
		amount = ++Deviceamount;
		scanneramount++;
		
		cout << "A new PoweredDevice is constructed." << endl;
		cout << "There are " << amount<< " PoweredDevices in total." << endl;
		cout << "A new Scanner is constructed." << endl;
		cout << "There are " << scanneramount << " Scanner in total." <<endl;
		return 0;
	}
};
class Printer : public Scanner
{
private:
	int amount = 0;
public:
	int printeramount;
	Printer()
	{
		printeramount = 0;
	}
	int createprinter()
	{
		stru[Deviceamount] = 1;
		amount = ++Deviceamount;
		printeramount++;
		cout << "A new PoweredDevice is constructed." << endl;
		cout << "There are " << amount << " PoweredDevices in total." << endl;
		cout << "A new Printer is constructed." << endl;
		cout << "There are " << printeramount << " Printer in total." << endl;
		return 0;
	}
};
class Copier : public Printer
{
private:
	int amount = 0;
public:
	int copieramount;
	Copier()
	{
		copieramount = 0;
	}
	int createcopier()
	{
		stru[Deviceamount] = 2;
		amount=++Deviceamount;
		printeramount++;
		scanneramount++;
		copieramount++;
		cout << "A new PoweredDevice is constructed." << endl;
		cout << "There are " <<amount<< " PoweredDevices in total." << endl;
		cout << "A new Scanner is constructed." << endl;
		cout << "There are " << scanneramount << " Scanner in total." << endl;
		cout << "A new Printer is constructed." << endl;
		cout << "There are " << printeramount << " Printer in total." << endl;
		cout << "A new Copier is constructed." << endl;
		cout << "There are " << copieramount << " Copiers in total." << endl;
		return 0;
	}
	int print()
	{
		cout << "The devices are:" << endl;
		int j=0;
		for (int i = 0; i < Deviceamount; i++)
		{
			if (stru[i] == 0)
			{
				cout << "Scanner";
				j++;
				if (j < Deviceamount)
					cout << endl;
			}
			if (stru[i] == 1)
			{
				cout << "Printer";
				j++;
				if (j < Deviceamount)
					cout << endl;
			}
			if (stru[i] == 2)
			{
				cout << "Copier";
				j++;
				if (j < Deviceamount)
					cout << endl;
			}
		}

		
		return 0;
	}
};

int main()
{
	string function;
	Copier machine;
	do
	{
		cin >> function;
		if (function.compare("s") == 0)
		{
			machine.createscanner();
		}
		if (function.compare("p") == 0)
		{
			machine.createprinter();
		}
		if (function.compare("c") == 0)
		{
			machine.createcopier();
		}
		if (function.compare("e") == 0)
		{
			machine.print();
			break;
		}
	} while (true);
	
	return 0;
}
