// Easy_GC.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CodeWriter.h"

using namespace std;
#include<iostream>
int _tmain(int argc, _TCHAR* argv[])
{
	using namespace CodeWriter;
	Variable *v1 = new Variable("this");
	Variable *v2 = new Variable("hah");
	vector<Variable*> p(1,new Variable("arg1"));
	FunctionEquation fe(v1, v2, p);
	cout<<fe.toString();
	return 0;
}

