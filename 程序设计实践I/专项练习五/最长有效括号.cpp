//#include "pch.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;
class Solution 
{
public:      
	int longestValidParentheses(string s)

	{
	
		stack<int> ss;          
		int max = 0;                        
		for( int i= 0; i< s.size() ; i++)
		{	              
			if( s[i] == ')' && !ss.empty() && s[ss.top()] == '(')
				//如果当前元素为），并且栈内不是空的，同时栈顶元素是(，那么
			{                  
				ss.pop();//将()出栈                 
				if( ss.empty())    //如果出栈后栈空了，那么由于i从0开始，所以长度+1               
					max = i+1;                  
				else               //如果出栈后栈还没空          
					if( i - ss.top() > max)      //如果当前元素位置减去栈顶元素位置比最大值大                   
						max = i - ss.top();      //那么最大值等于这个距离      
			}             
			else//如果当前元素为（，或栈是空的，都将这个元素入栈
				ss.push(i);         
		}          
	return max;   
	}  
};  
int main()
{
	string str;
	stack<int> ack;
	Solution a;
	cin >> str;
	cout << a.longestValidParentheses(str);
	return 0;
}
