#include "stdafx.h"
#include <iostream>
#include <vector>
#include "CodeGenerator.h"


/******************************************************************************************
CodeGenerator
*******************************************************************************************/
namespace CodeGenerator
{
void CodeGenerator:: printStatement()
{
	cout<<s->toString();
};

string CodeGenerator:: toString(int n)
{
	return s->toString(n);
}
CodeGenerator::~CodeGenerator()
{
	delete s;
}
}
/******************************************************************************************
Range
*******************************************************************************************/

namespace CodeGenerator
{
	vector<Range* > Range:: getRanges(string str)
	{
		vector<Range* > ranges;
		if(str.empty())
			return ranges;
		str.push_back(';');
		int length = str.length();
		//look for two :
		int startIndex = 0;
		while(-1 != str.find(';', startIndex))
		{
			int newStart = str.find(';', startIndex);
			ranges.push_back(Range::getRange(str.substr(startIndex, newStart-startIndex)));
			startIndex = newStart+1;
		}
		return ranges;
	}

	vector<vector<Range* > > Range:: getComboRanges(string str)
	{
		vector<vector<Range* > > comboRanges;
		if(str.empty())
			return comboRanges;
		str.push_back(';');
		int length = str.length();
		//look for two :
		int startIndex = 0;
		while(-1 != str.find(';', startIndex))
		{
			int newStart = str.find(';', startIndex);
			comboRanges.push_back(Range::getComboRange(str.substr(startIndex, newStart-startIndex)));
			startIndex = newStart+1;
		}
		return comboRanges;
	}

	Range* Range:: getRange(string str)
	{
		if(-1 == str.find(':'))
			return new SingleRange(str);
		else
			return new MultipleRange(str);
	}
	//seperate by ','
	vector<Range* > Range:: getComboRange(string str)
	{
		vector<Range* > comboRange;
		str.push_back(',');
		int lastI = 0;
		int curI = str.find(',', lastI);
		while(-1 != curI)
		{
			comboRange.push_back(Range::getRange(str.substr(lastI, curI-lastI)));
			lastI = curI+1;
			curI = str.find(',', lastI);
		}
		return comboRange;
	}

	bool Range::isMultiple()
	{
		return this->multiple;
	}

	string Range::getVariable()
	{
		return "";
	}

	string Range::getVariable(string variable)
	{
		return "";
	}

	string Range::getNum()
	{
		return "1";
	}

}

/******************************************************************************************
SingleRange
*******************************************************************************************/
namespace CodeGenerator
{
	SingleRange::SingleRange(string str)
	{
		this->index = str;
		this->multiple = false;
	}

	string SingleRange::getVariable()
	{
		return index;
	}
	string SingleRange::getVariable(string variable)
	{
		return index;
	}
}

/******************************************************************************************
MultipleRange
*******************************************************************************************/
namespace CodeGenerator
{

	MultipleRange::MultipleRange(string str)
	{
		int index1 = str.find_first_of(':');
		int index2 = str.find_last_of(':');
		this->startIndex = str.substr(0, index1);
		this->num = str.substr(index2+1);
		this->step = str.substr(index1+1, index2-index1-1);
		this->multiple = true;
	}

	string MultipleRange::getVariable()
	{
		return this->startIndex+"+i*"+this->step;
	}
	string MultipleRange::getVariable(string variable)
	{
		return this->startIndex+"+"+variable+"*"+this->step;
	}

	string MultipleRange::getNum()
	{
		return this->num;
	}
}

/**********************************************************************************
*Initialtor
**********************************************************************************/
namespace CodeGenerator
{
Initialtor::Initialtor()
{
}
Initialtor::~Initialtor()
{
}
Initialtor::Initialtor(string ci, string arg, string cn)
{
	this->circuitIndexes = ci;
	this->arguments = arg;
	this->className = cn;
}

//; to seperate vector, so 
void Initialtor:: setStatement()
{
	Range* circuitIndexRange = Range::getRange(circuitIndexes);
	vector<Range* >  circuitArgumentsRange = Range::getComboRange(arguments);
	
	s = generateStatement(circuitIndexRange, circuitArgumentsRange);
};

Statement* Initialtor::generateStatement(Range* cir, vector<Range* > pir)
{
	ForLoopStatement *fls = 0;
	//need for loop
	if(cir->isMultiple())
	{
		//may set forloop variable here
		//to match the range
		fls = new ForLoopStatement(cir->getNum(), "i");
	}
	vector<string> parameters;
	for(int i=0; i<pir.size(); i++)
		parameters.push_back(pir[i]->getVariable());
	InitialtorStatement *is = new InitialtorStatement(cir->getVariable("i"), parameters, this->className);
	if(0 != fls)
	{
		fls->insertToForLoop(is);
		return fls;
	}
	else
		return is;	
}

}

/******************************************************************************************
FixedWire
*******************************************************************************************/
namespace CodeGenerator
{

	FixedWire::FixedWire(string ci, string psi, string pi, string v):circuitIndexes(ci), portStartIndex(psi), portIndexes(pi), value(v)
	{
	};
	void FixedWire::setStatement()
	{
		
		//first loop the circuitIndex
		Range *r1 = Range::getRange(circuitIndexes);
		ForLoopStatement *f1 = 0;
		if(r1->isMultiple())
			f1 = new ForLoopStatement(r1->getNum(), "i");

		//second loop index start
		Range *r2 = Range::getRange(portStartIndex);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");
		
		//third loop
		Range *r3 = Range::getRange(portIndexes);
		ForLoopStatement *f3 = 0;
		if(r3->isMultiple())
			f3 = new ForLoopStatement(r3->getNum(), "k");
		

		Statement *fw = new FixedWireStatement(r1->getVariable(),r2->getVariable()+"+"+r3->getVariable(), value);
		
		if(0 != f1)
		{
			f1->insertToForLoop(f2);
			f1->insertToForLoop(f3);
			f1->insertToForLoop(fw);
			s = f1;
		}
		else
		if(0 != f2)
		{
			f2->insertToForLoop(f3);
			f2->insertToForLoop(fw);
			s = f2;
		}
		else
		if(0 != f3)
		{
			f3->insertToForLoop(fw);
			s = f3;
		}
		else
			s = fw;
		
	}
}
/******************************************************************************************
Connection
*******************************************************************************************/

// only one sentence
namespace CodeGenerator
{
	
	Connection::Connection(Component* sc, Component* dc):sourceCircuit(sc), destinationCircuit(dc)
	{
	}
	void Connection::setStatement()
	{
		//may include for loop?
		Statement *cs = sourceCircuit->generateStatement();
		cs->insertDesCircuit(this->destinationCircuit->getCircuitVariable());
		cs->insertDesInport(this->destinationCircuit->getPortVariable());
		s = cs;
	}
}
/******************************************************************************************
Component
*******************************************************************************************/
namespace CodeGenerator
{
	Component::Component(string pi):portIndex(pi)
	{}

	Statement * Component::generateStatement()
	{
		ForLoopStatement *fl = generateForLoopStatement();
		Statement *ic = getStatement();
		if(0 != fl)
		{
			fl->insertToForLoop(ic);
			return fl;
		}
		else
			return ic;
	}

	ForLoopStatement* Component::generateForLoopStatement()
	{
		ForLoopStatement *f1 = getForLoopStatement("i");
		//second loop
		Range *r2 = Range::getRange(this->portIndex);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");
		if(0 != f1)
		{
			f1->insertToForLoop(f2);
			return f1;
		}
		else
			return f2;
	}
}

/******************************************************************************************
SingleComponent
*******************************************************************************************/
namespace CodeGenerator
{

	SingleComponent::SingleComponent(string ci, string si, string port): Component(port), startIndexRange(si), circuitIndex(ci)
	{
	}

	string SingleComponent::getCircuitVariable()
	{
		//should be single
		Range * r = Range::getRange(this->circuitIndex);
		if(r->isMultiple())
			cout<<"multiple range in single component\n";
		return r->getVariable();
	}
	string SingleComponent::getPortVariable()
	{
		string result = "";
		Range *r1 = Range::getRange(this->startIndexRange);
		if(!r1->isMultiple())
			result += r1->getVariable();
		else
			result += r1->getVariable("i");

		Range *r2 = Range::getRange(this->portIndex);
		if(!r2->isMultiple())
			if(result.empty())
				result = r2->getVariable();
			else
				result += "+"+r2->getVariable();
		else
			if(result.empty())
				result = r2->getVariable("j");
			else
				result += "+"+r2->getVariable("j");

		return result;
	}
	Statement* SingleComponent::getStatement()
	{
		InterConnectionStatement *ic = new InterConnectionStatement(getCircuitVariable(), getPortVariable());
		return ic;
	};
	ForLoopStatement* SingleComponent::getForLoopStatement(string variable)
	{
		Range *r1 = Range::getRange(startIndexRange);
		ForLoopStatement *f1 = 0;
		if(r1->isMultiple())
			f1 = new ForLoopStatement(r1->getNum(), variable);
		return f1;
	}
}
/******************************************************************************************
MultipleComponent
*******************************************************************************************/
namespace CodeGenerator
{
	string MultipleComponent:: getCircuitVariable()
	{
		Range *r1 = Range::getRange(circuitIndexes);
		if(r1->isMultiple())
			cout<<"single range in multiple componnet\n";
		return r1->getVariable("i");
	}

	string MultipleComponent::getPortVariable()
	{
		Range *r2 = Range::getRange(this->portIndex);		
		return r2->getVariable("j");
	}
	MultipleComponent::MultipleComponent(string ci, string port):Component(port), circuitIndexes(ci)
	{
	}
	ForLoopStatement* MultipleComponent::getForLoopStatement(string variable)
	{
		Range *r1 = Range::getRange(circuitIndexes);
		ForLoopStatement *f1 = 0;
		if(r1->isMultiple())
			f1 = new ForLoopStatement(r1->getNum(), variable);
		return f1;
	}

	Statement* MultipleComponent::getStatement()
	{
		InterConnectionStatement *ic = new InterConnectionStatement(getCircuitVariable(), getPortVariable());
		return ic;
	};
}
/******************************************************************************************
Input
*******************************************************************************************/
namespace CodeGenerator
{
	Input::Input(string ip, string port):SingleComponent("",ip, port)
	{
	};
	Statement* Input::getStatement()
	{
		Statement* ic = new InputConnectionStatement(getPortVariable());
		return ic;
	}

}

/******************************************************************************************
Output
*******************************************************************************************/
namespace CodeGenerator
{
	Output::Output(string ip, string port):SingleComponent("", ip, port)
	{
	};
	Statement* Output::getStatement()
	{
		Statement* ic = new OutputConnectionStatement(getPortVariable());
		return ic;
	}

}

/******************************************************************************************
InputConnection
*******************************************************************************************/
namespace CodeGenerator
{
	InputConnection::InputConnection(string inputStartIndex, string sc, Component* endpoint):Connection(new Input(inputStartIndex, sc), endpoint)
	{
	}
	
}

/******************************************************************************************
OutputConnection
*******************************************************************************************/
namespace CodeGenerator
{
	OutputConnection::OutputConnection(string inputStartIndex, string sc, Component* endpoint):Connection(new Output(inputStartIndex, sc), endpoint)
	{
	}
}

/******************************************************************************************
GarbledClass
*******************************************************************************************/
namespace CodeGenerator
{
	GarbledClass::GarbledClass(string cn, string as, string in, string out, string component)
		:className(cn), arguments(as), inDegree(in), outDegree(out), componentNum(component)
	{
	}
	void GarbledClass::setStatement()
	{
		string str = "";
		vector<string> para;
		int length = arguments.length();
		for(int i=0; i<=length; i++)
		{
			char tmp = arguments[i];
			if(','==tmp||';'==tmp||'\0'==tmp)
			{
				if(!str.empty())
					para.push_back(str);
				str = "";
			}
			else
				str.push_back(tmp);
		}
		s = new GarbledClassFunction(className, para, inDegree, outDegree, componentNum);
	}

	string GarbledClass::getClassName()
	{
		return this->className;
	}
}