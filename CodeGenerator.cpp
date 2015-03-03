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
	for(auto it=s.begin(); it!=s.end(); it++)
		cout<<(*it)->toString();
};
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
		return variable;
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
		this->endIndex = str.substr(index2+1);
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
		return this->endIndex;
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
	for(auto it=s.begin(); it!=s.end(); it++)
		delete *it;
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
	vector<Range* > circuitIndexRanges = Range::getRanges(circuitIndexes);
	vector<vector<Range* > > circuitArgumentsRanges = Range::getComboRanges(arguments);
	if(circuitIndexRanges.size() == circuitArgumentsRanges.size())
	{
		for(int i=0; i<circuitIndexRanges.size(); i++)
		{
			s.push_back(generateStatement(circuitIndexRanges[i], circuitArgumentsRanges[i]));
		}
	}
};

Statement* Initialtor::generateStatement(Range* cir, vector<Range* > pir)
{
	ForLoopStatement *fls = 0;
	//need for loop
	if(cir->isMultiple())
	{
		//may set forloop variable here
		//to match the range
		fls = new ForLoopStatement();
	}
	vector<string> parameters;
	for(int i=0; i<pir.size(); i++)
		parameters.push_back(pir[i]->getVariable());
	InitialtorStatement *is = new InitialtorStatement(cir->getVariable(), parameters, this->className);
	if(0 != fls)
	{
		fls->insert(is);
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
		if(0 != f1)
			s.push_back(f1);
		//second loop index start
		Range *r2 = Range::getRange(portStartIndex);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");
		if(0 != f1 && 0!= f2)
			f1->insert(f2);
		if(0==f1&&0!=f2)
			s.push_back(f2);
		//third loop
		Range *r3 = Range::getRange(portIndexes);
		ForLoopStatement *f3 = 0;
		if(r3->isMultiple())
			f3 = new ForLoopStatement(r3->getNum(), "k");
		if(0 != f2 && 0!=f3)
			f2->insert(f3);
		else
		if(0 != f1 && 0 != f3)
			f1->insert(f3);
		if(f1==0&&f2==0&&f3!=0)
			s.push_back(f3);

		Statement *fw = new FixedWireStatement(r1->getVariable(),r2->getVariable()+"+"+r3->getVariable(), value);
		if(0 != f3)
			f3->insert(fw);
		else
		if(0 != f2)
			f2->insert(fw);
		else
		if(0 != f1)
			f1->insert(f2);
		else
		{
			s.push_back(fw);
			return;
		}
		
	}
}
/******************************************************************************************
Connection
*******************************************************************************************/

// only one sentence
namespace CodeGenerator
{
	
	Connection::Connection(string sp, string dp, Component* sc, Component* dc):srcPortIndex(sp), dstPortIndex(dp), sourceCircuit(sc), destinationCircuit(dc)
	{
	}
	void Connection::setStatement()
	{
		//may include for loop?
		Statement *cs = sourceCircuit->getStatement(this->srcPortIndex);
		cs->insertDesCircuit(this->destinationCircuit->getCircuitVariable());
		cs->insertDesInport(this->destinationCircuit->getPortVariable(this->dstPortIndex));
		s.push_back(cs);
	}
}

/******************************************************************************************
SingleComponent
*******************************************************************************************/
namespace CodeGenerator
{

	SingleComponent::SingleComponent(string si, string ci): startIndexRange(si), circuitIndex(ci)
	{
	}

	string SingleComponent::getCircuitVariable()
	{
		Range * r = Range::getRange(this->circuitIndex);
		return r->getVariable();
	}
	string SingleComponent::getPortVariable(string srcPort)
	{
		Range *r1 = Range::getRange(this->startIndexRange);
		Range *r2 = Range::getRange(srcPort);
		return r1->getVariable("i")+"+"+r2->getVariable("j");
	}
	Statement* SingleComponent::getStatement(string ip)
	{
		ForLoopStatement *f1 = getForLoopStatement("i");
		//second loop
		Range *r2 = Range::getRange(ip);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");
		InterConnectionStatement *ic = new InterConnectionStatement(getCircuitVariable(), getPortVariable(ip));
		if(0 != f2)
			f2->insert(ic);
		if(0 != f1)
			if(0 != f2)
				f1->insert(f2);
			else
				f1->insert(ic);
		if(0 != f1)
			return f1;
		if(0 != f2)
			return f2;
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
		return r1->getVariable();
	}

	string MultipleComponent::getPortVariable(string src)
	{
		Range *r2 = Range::getRange(src);
		return r2->getVariable();
	}
	MultipleComponent::MultipleComponent(string ci):circuitIndexes(ci)
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

	Statement* MultipleComponent::getStatement(string ip)
	{
		ForLoopStatement *f1 = getForLoopStatement("i");
		//second loop
		Range *r2 = Range::getRange(ip);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");
		InterConnectionStatement *ic = new InterConnectionStatement(getCircuitVariable(), getPortVariable(ip));
		if(0 != f2)
			f2->insert(ic);
		if(0 != f1)
			if(0 != f2)
				f1->insert(f2);
			else
				f1->insert(ic);
		if(0 != f1)
			return f1;
		if(0 != f2)
			return f2;
		return ic;
	};
}
/******************************************************************************************
Input
*******************************************************************************************/
namespace CodeGenerator
{
	Input::Input(string ip):SingleComponent(ip, "")
	{
	};
	Statement* Input::getStatement(string ip)
	{
		//the first loop startIndex
		Range *r1 = Range::getRange(startIndexRange);
		ForLoopStatement *f1 = 0;
		if(r1->isMultiple())
			f1 = new ForLoopStatement(r1->getNum(), "i");
		//second loop
		Range *r2 = Range::getRange(ip);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");

		Statement* ic = new InputConnectionStatement(r1->getVariable("i")+"+"+r2->getVariable("j"));

		if(0 != f2)
			f2->insert(ic);
		if(0 != f1)
			if(0 != f2)
				f1->insert(f2);
			else
				f1->insert(ic);
		if(0 != f1)
			return f1;
		if(0 != f2)
			return f2;
		return ic;
	}

}

/******************************************************************************************
Output
*******************************************************************************************/
namespace CodeGenerator
{
	Output::Output(string ip):SingleComponent(ip, "")
	{
	};
	Statement* Output::getStatement(string ip)
	{
		//the first loop startIndex
		Range *r1 = Range::getRange(startIndexRange);
		ForLoopStatement *f1 = 0;
		if(r1->isMultiple())
			f1 = new ForLoopStatement(r1->getNum(), "i");
		//second loop
		Range *r2 = Range::getRange(ip);
		ForLoopStatement *f2 = 0;
		if(r2->isMultiple())
			f2 = new ForLoopStatement(r2->getNum(), "j");

		Statement* ic = new OutputConnectionStatement(r1->getVariable("i")+"+"+r2->getVariable("j"));

		if(0 != f2)
			f2->insert(ic);
		if(0 != f1)
			if(0 != f2)
				f1->insert(f2);
			else
				f1->insert(ic);
		if(0 != f1)
			return f1;
		if(0 != f2)
			return f2;
		return ic;
	}

}

/******************************************************************************************
InputConnection
*******************************************************************************************/
namespace CodeGenerator
{
	InputConnection::InputConnection(string inputStartIndex, Component* endpoint, string sc, string rc):Connection(sc, rc, new Input(inputStartIndex), endpoint)
	{
	}
	
}

/******************************************************************************************
OutputConnection
*******************************************************************************************/
namespace CodeGenerator
{
	OutputConnection::OutputConnection(string inputStartIndex, Component* endpoint, string sc, string rc):Connection(sc, rc, new Output(inputStartIndex), endpoint)
	{
	}
}

