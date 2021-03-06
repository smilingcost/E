// final.cpp: 定义控制台应用程序的入口点。
//本项目融合了first项目和compile项目
// first.cpp: 定义控制台应用程序的入口点。
//
/*遇到问题，3e2)先输出e2,在输出3)*/
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <stack>
#include <vector>

using namespace std;
char s[10000], sss[10000];
//a = c * ( 1.2 + 25 ) / b - 3e2
//定义关键字
string keyword[29] = { "if","then","call","while","do","static","defualt","begin","end"
"int","double","struct","break","else","long","swtich","case","typedf","const",
"var","char","return","const","float","short","continue","for","void","sizeof" };
//定义运算符
char symbol[9] = { '+','-','*','/','=' };
//定义界限符
char symbol2[3] = { '(',')','#' };
vector<char> v1;//i和E的分析栈
vector<char> v2;//i和E的符号栈
vector<string> v3;//代码的分析栈
vector<string> v4;//代码的符号栈
vector<char>::iterator it;
vector<string>::iterator pit;
int index = 0;
char b[11][11] =
{
	{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','>' },
	{ ' ',' ',' ','>','>','>','>','>','>','>','>' },
	{ ' ',' ',' ','=','=','=','=',' ',' ','=','>' },
	{ ' ',' ','=',' ',' ',' ',' ',' ',' ',' ','>' },
	{ ' ',' ','=',' ',' ',' ',' ',' ',' ',' ','>' },
	{ ' ',' ','=',' ',' ',' ',' ',' ',' ',' ','>' },
	{ ' ',' ','=',' ',' ',' ',' ',' ',' ',' ','>' },
	{ ' ',' ','=',' ',' ',' ',' ',' ',' ',' ','>' },
	{ ' ',' ','=','>','>','>','>','>',' ',' ','>' },
	{ ' ',' ',' ','>','>','>','>',' ',' ',' ','>' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
};


//清空赋值语句中的空格
void ClearSpace(vector <char> &v) {
	vector <char> ::iterator it1;
	for (it1 = v.begin();it1 != v.end();it1++) {
		if (*it1 == ' ') {
			it1 = v.erase(it1);
		}
	}
}

//关键字判断  
int Iskey(string s)
{
	int i;
	for (i = 0;i<29;i++)
	{
		if (keyword[i] == s)
			return 1;
	}
	return 0;
}

//判断是否为字母  
int IsLetter(char c)
{
	if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A')))
		return 1;
	else
		return 0;
}

//判断是否为数字  
int IsDigit(char c)
{
	if (c >= '0'&&c <= '9')
		return 1;
	else
		return 0;
}

//运算符判断  
int IsSy(char c)
{
	int i;
	for (i = 0;i<9;i++)
	{
		if (symbol[i] == c)
			return 1;
	}
	return 0;
}

//界限符判断  
int IsSy2(char c)
{
	int i;
	for (i = 0;i<3;i++)
	{
		if (symbol2[i] == c)
			return 1;
	}
	return 0;
}

//指数判断
int IsE(vector <char> ::iterator &it1) {
	ofstream fou;
	string filename = "F://c_plusplus_project/final/final/temp.txt";
	fou.open(filename,ios::app);
	cout << *it1;
	fou << *it1;
	it1++;
	if (IsDigit(*it1) || *it1 == '-') {
		if (*it1 == '-') {
			cout << *it1;
			fou << *it1;
			it1++;
			if (IsDigit(*it1)) {
				for (it1;IsDigit(*it1);it1++) {
					cout << *it1;
					fou << *it1;
				}
				cout << "是指数" << endl;
				fou << endl;
				it1--;
			}
			else {
				cout << "e之后不是数字" << endl;
				system("pause");
				fou.close();
				return 0;
			}
		}
		else {
			for (it1;IsDigit(*it1);it1++) {
				cout << *it1;
				fou << *it1;
			}
			cout << "是指数" << endl;
			fou << endl;
			it1--;
			fou.close();
			return 1;
		}
	}
	else {
		cout << "e之后不是数字" << endl;
		system("pause");
		fou.close();
		return 0;
	}
	fou.close();
}

//获得词法分析之后的文件内容
char* getData() {
	ifstream in;
	string filename = "F://c_plusplus_project/final/final/data.txt";
	char buf[1024];
	in.open(filename);
	in.getline(buf, sizeof(buf));
	in.close();
	return buf;
}

//输出符号栈和分析栈的相关信息
void out(vector<char> v1, vector<char> v2, vector<char>::iterator it) {
	for (it = v1.begin();it != v1.end();it++) {
		cout << *it;
	}
	cout << "          ";
	for (it = v2.begin();it != v2.end();it++) {
		cout << *it;
	}
	cout << endl;
}

//用于根据符号转换成优先关系矩阵中的数字
int replace(char ch) {
	int t = 0;
	switch (ch) {
	case 'S':
		t = 0;
		break;
	case 'i':
		t = 1;
		break;
	case 'E':
		t = 2;
		break;
	case '+':
		t = 3;
		break;
	case '-':
		t = 4;
		break;
	case '*':
		t = 5;
		break;
	case '/':
		t = 6;
		break;
	case '=':
		t = 7;
		break;
	case '(':
		t = 8;
		break;
	case ')':
		t = 9;
		break;
	case '#':
		t = 10;
		break;
	}
	return t;
}

//归约函数
void reduce(vector<char> &v1, vector<char> &v2, vector<string> &v3, vector<string> &v4) {
	ofstream ffout;
	string filename = "F://c_plusplus_project/final/final/quaternary.txt";
	ffout.open(filename,ios::app);
	int flag = 0;
	if (*it == 'E'&&*(it - 1) == '+'&&*(it - 2) == 'E') {
		flag = 1;
		index++;
		ffout << '(' << *(pit - 1) << ',' << *(pit - 2) << ',' << *pit <<','<< index << ')' << endl;
		for (int i = 0;i < 3;i++) {
			v1.erase(it--);
			v3.erase(pit--);
		}
		v1.push_back('E');
		v3.push_back(to_string(index));
	}
	else if (*it == 'E'&&*(it - 1) == '-'&&*(it - 2) == 'E') {
		flag = 1;
		index++;
		ffout << '(' << *(pit - 1) << ',' << *(pit - 2) << ',' << *pit << ',' << index << ')' << endl;
		for (int i = 0;i < 3;i++) {
			v1.erase(it--);
			v3.erase(pit--);
		}
		v1.push_back('E');
		v3.push_back(to_string(index));
	}
	else if (*it == 'E'&&*(it - 1) == '*'&&*(it - 2) == 'E') {
		flag = 1;
		index++;
		ffout << '(' << *(pit - 1) << ',' << *(pit - 2) << ',' << *pit << ',' << index << ')' << endl;
		for (int i = 0;i < 3;i++) {
			v1.erase(it--);
			v3.erase(pit--);
		}
		v1.push_back('E');
		v3.push_back(to_string(index));
	}
	else if (*it == 'E'&&*(it - 1) == '/'&&*(it - 2) == 'E') {
		flag = 1;
		index++;
		ffout << '(' << *(pit - 1) << ',' << *(pit - 2) << ',' << *pit << ',' << index << ')' << endl;
		for (int i = 0;i < 3;i++) {
			v1.erase(it--);
			v3.erase(pit--);
		}
		v1.push_back('E');
		v3.push_back(to_string(index));
	}
	else if (*it == ')'&&*(it - 1) == 'E'&&*(it - 2) == '(') {
		flag = 1;
		index++;
		ffout << '(' << *(pit - 1) << ',' << *(pit - 2) << ',' << *pit << ',' << index << ')' << endl;
		for (int i = 0;i < 3;i++) {
			v1.erase(it--);
			v3.erase(pit--);
		}
		v1.push_back('E');
		v3.push_back(to_string(index));
	}
	else if (*it == 'E'&&*(it - 1) == '='&&*(it - 2) == 'E') {
		flag = 1;
		ffout << '(' << *(pit - 1) << ',' << *(pit - 2) << ',' << '-' << ',' << index << ')' << endl;
		for (int i = 0;i < 3;i++) {
			v1.erase(it--);
			v3.erase(pit--);
		}
		v1.push_back('S');
		v3.push_back(to_string(index));
	}
	if (flag) {
		cout << "归约";
		out(v1, v2, it);
	}
	ffout.close();
}

int main() {
	/*词法分析*/
	vector <char> v;
	vector <char> ::iterator it1;
	ifstream in;
	string filename = "F://c_plusplus_project/final/final/input.txt";
	in.open(filename);
	in.getline(s, sizeof(s));
	in.close();
	ofstream fout;
	filename = "F://c_plusplus_project/final/final/data.txt";
	fout.open(filename);
	ofstream fou;
	filename = "F://c_plusplus_project/final/final/temp.txt";
	fou.open(filename,ios::app);
	//将赋值语句放入vector
	for (int i = 0;i<strlen(s);i++) {
		v.push_back(s[i]);
	}
	//清空赋值语句中的空格符号
	ClearSpace(v);
	//开始分析
	for (it1 = v.begin();it1 != v.end();it1++) {
		if (IsLetter(*it1)) {
			memset(sss, 0, sizeof(sss));
			int index = 0;
			cout << *it1;
			fou << *it1;
			sss[index++] = *it1;
			it1++;
			for (it1;IsLetter(*it1) || *it1 == '_';it1++) {
				cout << *it1;
				fou << *it1;
				sss[index++] = *it1;
				if (it1 == v.end() - 1) {
					if (Iskey(sss)) {
						cout << "是关键字" << endl;
						fou << endl;
						fout << 'i';
					}
					else {
						cout << "是标识符" << endl;
						fou << endl;
						fout << 'i';
					}
					/*cout<<"是字母"<<endl;*/
					system("pause");
					return 0;
				}
			}
			if (Iskey(sss)) {
				cout << "是关键字" << endl;
				fou << endl;
				fout << 'i';
			}
			else {
				cout << "是标识符" << endl;
				fou << endl;
				fout << 'i';
			}
			//cout<<"是字母"<<endl;
			*it1--;
		}
		else if (IsDigit(*it1)) {
			cout << *it1;
			fou << *it1;
			fou.close();
			fou.open(filename, ios::app);
			it1++;
			for (it1;IsDigit(*it1);it1++) {
				cout << *it1;
				fou << *it1;
			}
			if (*it1 == '.') {
				cout << *it1;
				fou << *it1;
				it1++;
				if (IsDigit(*it1)) {
					for (it1;IsDigit(*it1);it1++) {
						cout << *it1;
						fou << *it1;
					}
					if (*it1 == 'e') {
						int temp = IsE(it1);
						if (temp) {
							fout << 'i';
						}
					}
					else {
						cout << "是小数" << endl;
						fou << endl;
						fout << 'i';
						it1--;
					}
				}
				else {
					cout << "小数点之后不是数字" << endl;
					system("pause");
					return 0;
				}
			}
			else if (*it1 == 'e') {
				int temp = IsE(it1);
				if (temp) {
					fout << 'i';
				}
			}
			else {
				cout << "是整数" << endl;
				fou << endl;
				fout << 'i';
				it1--;
			}
		}
		else if (IsSy(*it1)) {
			cout << *it1 << "是运算符" << endl;
			fou << *it1;
			fou << endl;
			fout << *it1;
		}
		else if (IsSy2(*it1)) {
			cout << *it1 << "是界限符" << endl;
			fou << *it1;
			fou << endl;
			fout << *it1;
		}
	}
	fout.close();




	/*语法分析*/
	fstream ftemp;
	ftemp.open("F://c_plusplus_project/final/final/temp.txt");
	string tt;
	while (getline(ftemp, tt)) //逐行读取，直到结束
	{
		v4.push_back(tt);//从temp.txt中读取一行，加入v4
	}
	char* temp = getData();
	char data[1024] = { 0 };
	memcpy(data, temp, sizeof(data));//不可以使用strcmp，不然会出错，data是语句
	for (int i = 0;i < strlen(data);i++) {
		v2.push_back(data[i]);
	}
	v1.push_back(v2.at(0));
	v2.erase(v2.begin());
	v3.push_back(v4.at(0));
	v4.erase(v4.begin());
	out(v1, v2, it);
	v1.push_back(v2.at(0));
	v2.erase(v2.begin());
	v3.push_back(v4.at(0));
	v4.erase(v4.begin());
	out(v1, v2, it);
	int times = 0;
	while ((v2.size() != 1) || (v1.size() != 2)) {
		it = v1.end() - 1;
		pit = v3.end() - 1;
		char ch1 = *it;
		int in1 = replace(ch1);
		char ch2 = v2.at(0);
		int in2 = replace(ch2);
		if ((b[in1][in2] == '<') || (b[in1][in2] == ' ') || (b[in1][in2] == '=')) {
			v1.push_back(v2.at(0));
			v2.erase(v2.begin());
			v3.push_back(v4.at(0));
			v4.erase(v4.begin());
			cout << "移入";
			out(v1, v2, it);
		}
		else {
			it = v1.end() - 1;
			pit = v3.end() - 1;
			if (*it == 'i') {
				*it = 'E';
				cout << "归约";
				out(v1, v2, it);
			}
			reduce(v1, v2, v3, v4);
		}
		times++;
		if (times > 100) {
			cout << "该语法错误" << endl;
			break;
		}
		if (v1.at(0) == '#'&&v1.at(1) == 'S'&&v2.at(0) == '#') {
			cout << "语法正确" << endl;
		}
	}
	system("pause");
	return 0;
}

