// Easy_GC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "CodeWriter.h"

using namespace std;
using namespace CodeGenerator;
using namespace CodeWriter;
#include<iostream>
int _tmain(int argc, _TCHAR* argv[])
{
	/*
	Initialtor initialtor("0:1:9", "1, 5", "text");
	initialtor.setStatement();
	initialtor.printStatement();
	*/
	/*
	Component *backEnd = new SingleComponent("0:1:2", "0");
	InputConnection *ic = new InputConnection("0:2:4", backEnd, "0:2:4", "0:4:8");
	ic->setStatement();
	ic->printStatement();
	*/
	/*
	Component *backEnd = new SingleComponent("0:1:2", "0");
	OutputConnection *oc = new OutputConnection("0:2:4", backEnd, "0:2:4", "0:4:8");
	oc->setStatement();
	oc->printStatement();
	*/
	/*
	Component *frontEnd = new SingleComponent("0:1:2", "0");
	Component *backEnd = new SingleComponent("0:1:2", "0");
	Connection *c = new Connection("1:2:2", "5:3:2",frontEnd, backEnd);
	c->setStatement();
	c->printStatement();
	*/
	/*
	Component *frontEnd = new MultipleComponent("0:1:2");
	Component *backEnd = new SingleComponent("0:1:2", "0");
	Connection *c = new Connection("1:2:2", "5:3:2",frontEnd, backEnd);
	c->setStatement();
	c->printStatement();
	*/
	FixedWire fw("1:2:2", "0", "3:4:5", "0");
	fw.setStatement();
	fw.printStatement();
	return 0;
}

