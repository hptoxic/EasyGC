// Easy_GC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "JavaClass.h"

using namespace std;
using namespace CodeGenerator;
using namespace CodeWriter;
#include<iostream>
int _tmain(int argc, _TCHAR* argv[])
{
	
	Initialtor initialtor("0:1:9", "1, 5", "text");
	//initialtor.setStatement();
	//initialtor.printStatement();
	
	
	Component *backEnd1 = new SingleComponent("0", "0:1:2", "0:2:4");
	InputConnection ic("0:2:2","0:2:4", backEnd1);
	//ic.setStatement();
	//ic.printStatement();
	
	Component *backEnd2 = new SingleComponent("0", "0:1:2", "0:2:4");
	OutputConnection oc("0:2:4", "0:4:8", backEnd2);
	//oc.setStatement();
	//oc.printStatement();
	
	
	Component *frontEnd1 = new SingleComponent("0", "0", "0:1:2");
	Component *backEnd3 = new SingleComponent("2", "3", "3:2:2");
	Connection c(frontEnd1, backEnd3);
	//c.setStatement();
	//c.printStatement();
	
	
	Component *frontEnd2 = new MultipleComponent("0:1:2", "2:3:4");
	Component *backEnd4 = new SingleComponent("0", "0:1:2", "3:5:4");
	Connection mc(frontEnd2, backEnd4);
	//mc.setStatement();
	//mc.printStatement();
	
	
	Component *frontEnd3 = new MultipleComponent("0:1:2", "2:3:4");
	Component *backEnd5 = new MultipleComponent("5:6:2", "3:5:4");
	Connection bc(frontEnd3, backEnd5);
	//bc.setStatement();
	//bc.printStatement();
	
	
	FixedWire fw("1:2:2", "0", "3:4:5", "0");
	//fw.setStatement();
	//fw.printStatement();
	
	GarbledClass gc("HAMMING", "L", "2L", "2L+1", "L+1");
	//gc.setStatement();
	//gc.printStatement();

	JavaClass::JavaClass jc(gc);
	jc.insert(initialtor);
	jc.insert(ic);
	jc.insert(oc);
	jc.insert(c);
	jc.insert(mc);
	jc.insert(bc);
	jc.insert(fw);
	cout<<jc.getFileContent();
	return 0;
}

