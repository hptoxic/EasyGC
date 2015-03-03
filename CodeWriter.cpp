#include "stdafx.h"
#include "CodeWriter.h"

/******************************************************************************************
*class Statement
*******************************************************************************************/
namespace CodeWriter {
	void Statement::insertDesCircuit(string str)
	{
	}
	void Statement::insertDesInport(string str)
	{
	}

}

/******************************************************************************************
*class InitialtorStatement
*******************************************************************************************/
namespace CodeWriter {

	string InitialtorStatement:: toString()
	{
		string output = "subCircuits["+index+"] = new "+className+"(";
		int size = arguments.size();
		for(int i=0; i<size; i++)
		{
			output += arguments[i];
			if(size-1 != i)
				output += ", ";
		}
		output += ");\n";
		return output;
	}

	InitialtorStatement::InitialtorStatement(string i, vector<string> a, string cn):index(i), arguments(a), className(cn)
	{
	}

	InitialtorStatement:: ~InitialtorStatement()
	{
	}

} /* namespace CodeWriter */

/******************************************************************************************
*class ConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

	void ConnectionStatement::insertDesCircuit(string str)
	{
		this->destinationCircuitId = str;
	}
	void ConnectionStatement::insertDesInport(string str)
	{
		destinationPortId = str;
	}
}

/******************************************************************************************
*class InterConnectionStatement
*******************************************************************************************/
namespace CodeWriter {
	string InterConnectionStatement:: toString()
	{
		string output = SUBCIRCUITS+"[";
		output += sourceCircuitId;
		output += "]."+OUTPUTWIRES+"[";
		output += sourcePortId;
		output += "]."+CONNECTTO+"("+SUBCIRCUITS+"[";
		output += destinationCircuitId;
		output += "]."+INPUTWIRES+", ";
		output += destinationPortId;
		output += ");\n";
		return output;
	}
	InterConnectionStatement:: InterConnectionStatement(string sc, string sp):sourceCircuitId(sc), sourcePortId(sp)
	{
	}

	InterConnectionStatement:: ~InterConnectionStatement()
	{
	}
}; /* namespace CodeWriter */



/******************************************************************************************
*class OutputConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

	string OutputConnectionStatement:: toString()
	{
		string output = OUTPUTWIRES+"[";
		output += outputPortId;
		output += "] = "+SUBCIRCUITS+"[";
		output += destinationCircuitId;
		output += "]."+OUTPUTWIRES+"[";
		output += destinationPortId;
		output += "];\n";
		return output;
	}
	OutputConnectionStatement::OutputConnectionStatement(string op):outputPortId(op)
	{
	}
}

/******************************************************************************************
*class InputConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

	string InputConnectionStatement:: toString()
	{
		string output = INPUTWIRES+"[";
		output += inputPortId;
		output += "]."+CONNECTTO+"("+SUBCIRCUITS+"[";
		output += destinationCircuitId;
		output += "]."+INPUTWIRES+", ";
		output += destinationPortId;
		output += ");\n";
		return output;
	};
	InputConnectionStatement::InputConnectionStatement(string ip):inputPortId(ip)
	{
	}

	InputConnectionStatement::~InputConnectionStatement()
	{
	}

} /* namespace CodeWriter */


/******************************************************************************************
*class FixedWireStatement
*******************************************************************************************/
namespace CodeWriter {
	string FixedWireStatement:: toString()
	{
		string output = SUBCIRCUITS+"[";
		output += inputCircuitId;
		output += "]."+INPUTWIRES+"[";
		output += inputPortId;
		output += "]."+FIXWIRE+"(";
		output += value;
		output += ");\n";
		return output;
	}

	FixedWireStatement::FixedWireStatement(string ic, string ip, string v):inputCircuitId(ic), inputPortId(ip), value(v)
	{
	}
};


/******************************************************************************************
*class ForLoopStatement
*******************************************************************************************/
namespace CodeWriter {
	string ForLoopStatement:: toString() 
	{
		string output = "for( int ";
		output += variable;
		output += "=";
		output += startIndex;
		output += "; ";
		output += variable;
		output += "<";
		output += endIndex;
		output += "; ";
		output += variable+"="+variable+"+"+step;
		output +=")\n{\n";
		for(auto it=statements.begin(); it!=statements.end(); it++)
			output += "\t"+(*it)->toString();
		output += "}\n";
		return output;
	}

	ForLoopStatement::~ForLoopStatement()
	{
		for(auto it=statements.begin(); it!=statements.end(); it++)
			delete *it;
	}

	void ForLoopStatement:: insert(Statement* s)
	{
		statements.push_back(s);
	}

	ForLoopStatement::ForLoopStatement()
	{
		this->startIndex = "0";
		this->endIndex = "end";
		this->step = "1";
		this->variable = "i";
	}

	ForLoopStatement::ForLoopStatement(string num, string variable)
	{
		this->startIndex = "0";
		this->endIndex = num;
		this->step = "1";
		this->variable = variable;
	}

	void ForLoopStatement::insertDesCircuit(string str)
	{
		for(auto it=statements.begin(); it!=statements.end(); it++)
			(*it)->insertDesCircuit(str);
	}

	void ForLoopStatement::insertDesInport(string str)
	{
		for(auto it=statements.begin(); it!=statements.end(); it++)
			(*it)->insertDesInport(str);
	}
};