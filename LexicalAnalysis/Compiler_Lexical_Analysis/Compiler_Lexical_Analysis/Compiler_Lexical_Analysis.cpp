// compiler_Lexical_Analyse.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctype.h>
#include <stdio.h>

using namespace std;

#define MAXLINE 1024
#define IS_IDENFR	1
#define IS_NUMBER	2
#define IS_CHAR		3
#define IS_STRING	4
#define IS_OPERATOR	5
#define IS_COMPARE	6
#define IS_BRAKET   7
#define IS_ASSIGN   8
#define IS_COMMA    9
#define IS_SEMICN   10

//get the const for find out what your word is;
FILE * fp;
int line;
string word;
char c;
string TKs[13][2] = { {"const", "CONSTTK"}, {"int", "INTTK"} , {"char", "CHARTK"}, 
	{"void", "VOIDTK"}, {"main", "MAINTK"}, {"if", "IFTK"}, {"else", "ELSETK"}, 
	{"do", "DOTK"}, {"while", "WHILETK"}, {"for", "FORTK"}, {"scanf", "SCANFTK"}, 
	{"printf", "PRINTFTK"}, {"return", "RETURNTK"} };

string OPERATORs[4][2] = { {"+", "PLUS"}, {"-", "MINU"}, {"*", "MULT"}, {"/", "DIV"} };

string COMPAREs[6][2] = { {"<", "LSS"} , {"<=", "LEQ"} , {">", "GRE"} ,
		{">=", "GEQ"} , {"==", "EQL"} , {"!=", "NEQ"} };

string BRAKETs[6][2] = { {"(", "LPARENT"} , {")", "RPARENT"} , {"[", "LBRACK"} , 
		{"]", "RBRACK"} , {"{", "LBRACE"} , {"}", "RBRACE"} };

int getwords();
void putwords(int a);

int main()
{
	char buf[MAXLINE];
	int len;
	int a;
	if ((fp = fopen("testfile.txt", "r")) == NULL) {
		perror("fail to read");
		return 1;
	}

	while ((a = getwords()) != -1) {
		putwords(a);
	}
	return 0;
}

void putwords(int a) {
	switch (a)
	{
	case IS_IDENFR:
		for (int i = 0; i < 13; i++) {
			if (word == TKs[i][0]) {
				cout << TKs[i][1] << " " << word << endl;
				return;
			}
		}
		cout << "IDENFR" << " " << word << endl;
		return;
	case IS_NUMBER:
		cout << "INTCON" << " " << word << endl;
		return;
	case IS_CHAR:
		cout << "CHARCON" << " " << word << endl;
		return;
	case IS_STRING:
		cout << "STRCON" << " " << word << endl;
		return;
	case IS_OPERATOR:
		for (int i = 0; i < 4; i++) {
			if (word == OPERATORs[i][0]) {
				cout << OPERATORs[i][1] << " " << word << endl;
				return;
			}
		}
	case IS_COMPARE:
		for (int i = 0; i < 6; i++) {
			if (word == COMPAREs[i][0]) {
				cout << COMPAREs[i][1] << " " << word << endl;
				return;
			}
		}
	case IS_BRAKET:
		for (int i = 0; i < 6; i++) {
			if (word == BRAKETs[i][0]) {
				cout << BRAKETs[i][1] << " " << word << endl;
				return;
			}
		}
	case IS_ASSIGN:
		cout << "ASSIGN" << " " << word << endl;
		return;
	case IS_COMMA:
		cout << "COMMA" << " " << word << endl;
		return;
	case IS_SEMICN:
		cout << "SEMICN" << " " << word << endl;
		return;
	default:
		break;
	}
	
	cout << word << endl;
}

int getwords() {
	word = "";
	c = fgetc(fp);
	while (c == ' ' || c == '	' || c == '\n') {
		c = fgetc(fp);
	}
	if (c == EOF) {
		return -1;
	}
	if (isalpha(c) || c == '_') {
		while ( c == '_' || isalnum(c)) {
			word += c;
			c = fgetc(fp);
		}
		fseek(fp, -1, 1);
		return IS_IDENFR;
	}
	if (isdigit(c)) {
		while (isdigit(c)) {
			word += c;
			c = fgetc(fp);
		}
		fseek(fp, -1, 1);
		return IS_NUMBER;
	}
	if ( c == '+' || c == '-' || c == '*' || c == '/') {
		word += c;
		return IS_OPERATOR; 
	}
	if ( c == '(' || c == ')' || c == '(' || c == '[' || c == ']' || c == '{' || c == '}') {
		word += c;
		return IS_BRAKET;
	}
	if (c == ',') {
		word += c;
		return IS_COMMA;
	}
	if (c == ';') {
		word += c;
		return IS_SEMICN;
	}
	if ( c == '<' || c == '>') {
		word += c;
		c = fgetc(fp);
		if ( c == '=') {
			word += c;
			return IS_COMPARE;
		}
		else {
			fseek(fp, -1, 1);
			return IS_COMPARE;
		}
	}
	if (c == '=') {
		word += c;
		c = fgetc(fp);
		if (c == '=') {
			word += c;
			return IS_COMPARE;
		}
		else {
			fseek(fp, -1, 1);
			return IS_ASSIGN;
		}
	}
	if (c == '!') {
		word += c;
		c = fgetc(fp);
		if (c == '=') {
			word += c;
			return IS_COMPARE;
		}
	}
	if (c == '\'') {
		c = fgetc(fp);
		word += c;
		c = fgetc(fp);
		if (c == '\'') {
			return IS_CHAR;
		}
	}
	if (c == '\"') {
		c = fgetc(fp);
		while (c != '\"') {
			word += c;
			c = fgetc(fp);
		}
		return IS_STRING;
	}
}
