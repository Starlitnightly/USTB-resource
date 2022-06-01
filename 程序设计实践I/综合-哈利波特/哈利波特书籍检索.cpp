#include "pch.h"
#include <sstream> 
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h> 
#include <regex>
#include <Windows.h>
#include<Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib") 


using namespace std;

class Book;
struct Numx;


/*书本类*/
class Book
{
public:
	string name;//书名
	string contact;//书的内容
	long int pages[4000];//书的页码
	long int chapter[500];//书的章节总数
	void Named(string names);//为这本书命名
	void readTxt(string file);//读取书的内容
	
};
struct Numx//总序号
{
	int book;//对应的具体数目
	int local;//对应的具体位置
};
/*为这本书命名*/
void Book::Named(string names)
{
	name = names;
}
/*读取这本书的内容，章节，页码*/
void Book::readTxt(string file)
{
	int i = 0;
	bool flag1=false;
	//将书本内容存到contact中
	fstream infile;
	infile.open(file.data(), ios::in);
	char c[2];	
	while (!infile.eof())
	{
		c[1] = '\0';
		infile.read(c, 1);
		if (c[0] == '\n')//当读入数据是回车时，flag=真，用于读取下一个字符时告诉程序上一个字符时回车
		{
			flag1 = true;
		}
		if (flag1 == true)
		{
			if (c[0] >= '0' && c[0] <= '9')//如果上一个字符是回车，且这个字符在0-9之间，那么一定是页码
			{
				c[0] = '@';
				flag1 = false;
			}
			else if(c[0] !='\n')
			{
				flag1 = false;
			}
		}
		contact += c[0];
	}
	
	infile.close();

	//将所有章节对应的具体位置存到chapter

	size_t fi = contact.find("Chapter", 0);
	if (fi == contact.npos)
	{
		fi = contact.find("CHAPTER", 0);
		while (fi != contact.npos)
		{
			chapter[i++] = fi;
			fi = contact.find("CHAPTER", fi + 1);
		}
	}
	else
	{
		while (fi != contact.npos)
		{
			chapter[i++] = fi;
			fi = contact.find("Chapter", fi + 1);
		}
	}
	
	//将所有页码对应的具体位置存到pages
	size_t fi1 = contact.find("@", 0);
	i = 0;
	while (fi1 != contact.npos)
	{
		pages[i++] = fi1;
		fi1 = contact.find("@", fi1 + 1);
	}

}

string TCHAR2STRING(TCHAR *STR)
{
	int iLen = WideCharToMultiByte(CP_ACP, 0,STR, -1, NULL, 0, NULL, NULL);
	char* chRtn = new char[iLen * sizeof(char)];
	WideCharToMultiByte(CP_ACP, 0, STR, -1, chRtn, iLen, NULL, NULL);
	std::string str(chRtn);
	delete chRtn;
	return str;
}
Numx numx[16000];//定义一个总索引，总索引指向了map的二维数组，将map的二维数组用一个序号储存]
long int map[8][2000];//每一本书内要搜索的单词具体的位置
int cha[8][2000];//每一本书要搜索的单词所在具体的章节
int pag[8][2000];//每一本书要检索的单词所在具体的页码
const void Search(const Book *book)
{
	int i = 0, j = 0, k = 0, m = 0;//j为章节的自增变量，m为页码的自增变量，保证章节与页码一直向前，读取新一本书的时候清空
	
	int outnum;
	
	string finding, midf;//finding是搜索内容，midf是输入内容，finding=空格+midf
	int begintime, endtime;//用于处理程序的运行时间

	/*输入搜索内容*/
	system("cls");
	cout << "成功加载哈利波特系列丛书" << endl << endl;
	cout << "输入你要检索的单词：" << endl;
	cin >> midf;
	finding += midf;
	begintime = clock();//取搜索开始时间

	/*按列表格式输出结果*/
	cout << setiosflags(ios::left) << setw(10) << "序号："
		<< setw(15) << "人名/地名："
		<< setw(10) << "页码："
		<< setw(10) << "章节："
		<< "书名：" << endl;

	/*搜索单词finding*/
	k = 0;
	for (int l = 0; l < 8; l++)//8本书挨个遍历
	{
		i = 0; j = 0; m = 0;

		size_t fi = book[l].contact.find(finding, 0);//搜索到的具体位置，size_t不定长
		while (fi != book[l].contact.npos)
		{

			map[l][i] = fi;//用map储存搜索到的具体位置
			while (1)//寻找该位置对应的章节
			{
				if (fi > book[l].chapter[j] && fi < book[l].chapter[j + 1])
					break;
				j++;
			}

			cha[l][i] = j;//输出该位置对应的章节
			while (1)//寻找该位置对应的章节
			{
				if (fi > book[l].pages[m] && fi < book[l].pages[m + 1])
					break;
				m++;
			}

			pag[l][i] = m;//输出该位置对应的章节
			numx[k].book = l;//每个总索引对应的具体map书号
			numx[k].local = i;//每个总索引对应的具体map序号

			/*按列表的格式输出结果*/
			if (k < 10)
			{
				cout << setiosflags(ios::left) << setw(10) << k
					<< setw(15) << midf
					<< setw(10) << pag[l][i]
					<< setw(10) << cha[l][i]
					<< book[l].name << endl;
			}

			i++; k++;//自增
			fi = book[l].contact.find(finding, fi + 1);
		}



	}
	endtime = clock();//取搜索结束时间

	

	if (k == 0)
	{
		cout << "无结果(输入-2搜索新的单词)" << endl;
		cin >> outnum;
		if (outnum == -2)
		{
			Search(book);
		}
	}
	else
	{
		cout << "Running Time：" << endtime - begintime << "ms" << endl;
		cout << "只显示前10项" << endl;
		cout << "总共有:" << k - 1 << "项" << endl;
		/*输出搜索结果*/
		do
		{
			cout << endl << "输入你要查看的序号，即可显示单词所在的句子。(按-1退出,-2搜索新的单词)" << endl;
			cin >> outnum;
			if (outnum > k - 1)
			{
				cout << "输入的序号不存在" << endl;
				continue;
			}
			if (outnum == -1)
				break;
			if (outnum == -2)
			{
				Search(book);
			}
			else
			{
				/*显示finding附近的100个单词,例如：book[1].contact[map[1][0]]*/
				int firstlocal, endlocal;
				firstlocal = book[numx[outnum].book].contact.find_last_of('.', map[numx[outnum].book][numx[outnum].local]);
				endlocal = book[numx[outnum].book].contact.find_first_of('.', map[numx[outnum].book][numx[outnum].local]);

				for (i = firstlocal + 1; i < endlocal + 1; i++)
					cout << book[numx[outnum].book].contact[i];
				cout << endl << endl;
			}
		} while (true);
	}
}

int main()
{
	int i = 0,j=0,k=0,m=0;//j为章节的自增变量，m为页码的自增变量，保证章节与页码一直向前，读取新一本书的时候清空
	long int map[8][2000];//每一本书内要搜索的单词具体的位置
	int cha[8][2000];//每一本书要搜索的单词所在具体的章节
	int pag[8][2000];//每一本书要检索的单词所在具体的页码
	int begintime, endtime;//用于处理程序的运行时间
	Book book[8];//定义7本书
	Numx numx[10000];//定义一个总索引，总索引指向了map的二维数组，将map的二维数组用一个序号储存
	string finding,midf;//finding是搜索内容，midf是输入内容，finding=空格+midf
	
	cout << "加载书目中..." << endl;
	
	/*取运行目录*/
	const int nBufSize = 512;
	TCHAR chBuf[nBufSize];
	ZeroMemory(chBuf, nBufSize);
	GetModuleFileName(NULL, chBuf, nBufSize);
	TCHAR* lpStrPath = chBuf;
	PathRemoveFileSpec(lpStrPath);
	string mid;
	mid = TCHAR2STRING(lpStrPath);


	/*导入8本书，八本书放在运行目录下*/
	book[0].Named("J.K. Rowling - HP 0 - Harry Potter Prequel");
	cout << mid + "\\1537835839070042080.txt" << endl;
	book[0].readTxt(mid+"\\1537835839070042080.txt");
	book[1].Named("HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_");
	cout << mid + "\\1537835838814021493.txt" << endl;
	book[1].readTxt(mid + "\\1537835838814021493.txt");
	book[2].Named("J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban");
	cout << mid + "\\1537835840376093816.txt" << endl;
	book[2].readTxt(mid + "\\1537835840376093816.txt");
	book[3].Named("HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_");
	cout << mid + "\\1537835838730035402.txt" << endl;
	book[3].readTxt(mid + "\\1537835838730035402.txt");
	book[4].Named("J.K. Rowling - Quidditch Through the Ages");
	cout << mid + "\\1537835855727087219.txt" << endl;
	book[4].readTxt(mid + "\\1537835855727087219.txt");
	book[5].Named("J.K. Rowling - The Tales of Beedle the Bard");
	cout << mid + "\\1537835857250083215.txt" << endl;
	book[5].readTxt(mid + "\\1537835857250083215.txt");
	book[6].Named("J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince");
	cout << mid + "\\1537835858108007396.txt" << endl;
	book[6].readTxt(mid + "\\1537835858108007396.txt");
	book[7].Named("J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire");
	cout << mid + "\\1537835854839084779.txt" << endl;
	book[7].readTxt(mid + "\\1537835854839084779.txt");
	
	Search(book);
	return 0;
}