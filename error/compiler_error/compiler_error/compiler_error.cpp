// compiler_error.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//error: this program is about how to find the error in the testfiles; 

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <cstring>
#include <cstdlib>

using namespace std;

#define MAXLINE 1024

int getsym(FILE* fp);

int main()
{
	char buf[MAXLINE];
	char c;
	FILE* fp;
	int len;
	if ((fp = fopen("testfile1.txt", "r")) == NULL) {
		perror("fail to read");
		return 1;
	}
	getsym(fp);
	return 0;
}

int getsym(FILE* fp) {
	char c;
	string strout = "";
	c = fgetc(fp);
	while (c == ' ' || c == '	' || c == '\n') {
		c = fgetc(fp);
	}
	while (c != EOF) {
		strout = "";
		while (c == ' ' || c == '	' || c == '\n') {
			c = fgetc(fp);
		}
		if (isalpha(c) || c == '_') {
			while (isalnum(c) || c == '_') {
				strout += c;
				c = fgetc(fp);
			}
			cout << strout << endl;
			continue;
		} 
		if (isdigit(c)) {
			while (isdigit(c)) {
				strout += c;
				c = fgetc(fp);
			}
			cout << strout << endl;
			c = fgetc(fp);
		}
		else if (c == ':') {
			c = fgetc(fp);
			if (c == '=') {
				cout << ":=" << endl;
				c = fgetc(fp);
			} 
			else {
				cout << ":" << endl;
			}
		}
		else if (c == '+' || c == '-' || c == '*' || c == '=' || c == '[' || c == ']'|| c == '/' || c == '(' || c == ')' || c == ',' || c == ';' ){
			cout << c << endl;
			c = fgetc(fp);
		}
		else if (c == '/') {
			c = fgetc(fp);
			if (c == '*') {
				c = fgetc(fp);
				while (1) {
					if (c == '*') {
						c = fgetc(fp);
						if (c == '/') {
							c = fgetc(fp);
							break;
						} 
						continue;
					}
					c = fgetc(fp);
				}
			}
			else if(c == '/') {
				while (c != '\n') {
					c = fgetc(fp);
				}
				c = fgetc(fp);
			}
			else {
				cout << "*" << endl;
				c = fgetc(fp);
			}
			fgetc(fp);
		}
	}
	return 0;
}

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
