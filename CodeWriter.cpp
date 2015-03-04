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
	void Statement::insertToForLoop(Statement* s)
	{
	};
}

/******************************************************************************************
*class InitialtorStatement
*******************************************************************************************/
namespace CodeWriter {

	string InitialtorStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+"subCircuits["+index+"] = new "+className+"(";
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
	string InterConnectionStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+SUBCIRCUITS+"[";
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

	string OutputConnectionStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+OUTPUTWIRES+"[";
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

	string InputConnectionStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+INPUTWIRES+"[";
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
	string FixedWireStatement:: toString(int n)
	{
		string indent(n, '\t');
		string output = indent+SUBCIRCUITS+"[";
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
	string ForLoopStatement:: toString(int n) 
	{
		string indent(n, '\t');
		string output = indent+"for( int ";
		output += variable;
		output += "=";
		output += startIndex;
		output += "; ";
		output += variable;
		output += "<";
		output += endIndex;
		output += "; ";
		output += variable+"="+variable+"+"+step;
		output +=")\n"+indent+"{\n";
		output += statement->toString(n+1);
		output += indent+"}\n";
		return output;
	}

	ForLoopStatement::~ForLoopStatement()
	{
		delete statement;
	}

	void ForLoopStatement:: insertToForLoop(Statement* s)
	{
		if(0 == statement)
			statement = s;
		else
			statement->insertToForLoop(s);
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
			statement->insertDesCircuit(str);
	}

	void ForLoopStatement::insertDesInport(string str)
	{
		statement->insertDesInport(str);
	}
};


/******************************************************************************************
*class GarbledClassFunction
*******************************************************************************************/
namespace CodeWriter {

	GarbledClassFunction::GarbledClassFunction(string cn, vector<string> as, string in, string out, string component)
		:className(cn), arguments(as), indegree(in), outdegree(out), componentNum(component)
	{}
	string GarbledClassFunction:: toString(int n)
	{
		string output = "";
		output += declareVariable(n);
		output += declareConstruction(n);
		return output;
	}

	string GarbledClassFunction::declareVariable(int n)
	{
		string indent(n, '\t');
		string output = "";
		for(auto it=arguments.begin(); it!=arguments.end(); it++)
			output += indent+"private final int "+(*it)+";\n";
		return output;
	}

	string GarbledClassFunction::declareConstruction(int n)
	{
		string indent(n, '\t');
		string output = "";
		//header
		output += indent+"public "+className+"(";
		int size = arguments.size();
		for(int i=0; i<size; i++)
		{
			output += "int "+arguments[i];
			if(size-1 != i)
				output += ", ";
		}
		output += ")\n";
		output += indent+"{\n";
		//call the father construction
		output += indent+"\tsuper("+indegree+", "+outdegree+", "+componentNum+", "+className+indegree+");\n";

		for(int i=0; i<size; i++)
			output += indent+"\tthis."+arguments[i]+" = "+arguments[i]+";\n";
		output += indent+"}\n";
		return output;
	}

} /* namespace CodeWriter */