/*
 * BinaryLinearEquation.h
 *
 *  Created on: Jan 29, 2015
 *      Author: yuw1
 */

#ifndef CODEWRITER_H_
#define CODEWRITER_H_
#include <string>
#include<vector>

using namespace std;

namespace CodeWriter {
class Statement;
class ForLoopStatement;
class ConnectionStatement;
class InitialtorStatement;
class InterConnectionStatement;
class OutputConnectionStatement;
class InputConnectionStatement;
class FixedWireStatement;
class GarbledClassFunction;
}
#include "CodeGenerator.h"

/******************************************************************************************
Variable
*******************************************************************************************/
namespace CodeWriter
{
	const string SUBCIRCUITS = "subCircuits";
	const string CONNECTTO = "connectTo";
	const string INPUTWIRES = "inputWires";
	const string OUTPUTWIRES = "outputWires";
	const string FIXWIRE = "fixWire";
};
/******************************************************************************************
*class Statement
*******************************************************************************************/
namespace CodeWriter {
class Statement {
public:
	//Statement();
	//virtual ~Statement();
	virtual string toString(int n = 0) = 0;
	virtual void insertDesCircuit(string str);
	virtual void insertDesInport(string str);
	virtual void insertToForLoop(Statement* s);
};

} /* namespace CodeWriter */

/******************************************************************************************
*class ConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

class ConnectionStatement: public Statement {
public:
	//ConnectionStatement();
	//virtual ~ConnectionStatement();
	virtual string toString(int n = 0)=0;
	void insertDesCircuit(string str);
	void insertDesInport(string str);
protected:
	string destinationCircuitId;
	string destinationPortId;
};

} /* namespace CodeWriter */




/******************************************************************************************
*class ForLoopStatement
*******************************************************************************************/
namespace CodeWriter {
class ForLoopStatement: public Statement {
public:
	ForLoopStatement();
	ForLoopStatement(string num, string variable);
	virtual ~ForLoopStatement();
	void insertToForLoop(Statement* s);
	string toString(int n = 0);
	virtual void insertDesCircuit(string str);
	virtual void insertDesInport(string str);
private:
	string startIndex;
	string endIndex;
	string step;
	string variable;
	Statement*  statement;
};

} /* namespace CodeWriter */

/******************************************************************************************
*class FixedWireStatement
*******************************************************************************************/
namespace CodeWriter {
class FixedWireStatement: public Statement {
public:
	FixedWireStatement(string ic, string ip, string v);
	//virtual ~FixedWireStatement();
	virtual string toString(int n = 0);
private:
	string inputCircuitId;
	string inputPortId;
	string value;
};

} /* namespace CodeWriter */

/******************************************************************************************
*class InitialtorStatement
*******************************************************************************************/
namespace CodeWriter {

class InitialtorStatement: public Statement {
public:
	InitialtorStatement(string i, vector<string> a, string cn);
	virtual ~InitialtorStatement();
	virtual string toString(int n = 0);
private:
	string index;
	vector<string> arguments;
	string className;
};

} /* namespace CodeWriter */

/******************************************************************************************
*class InterConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

class InterConnectionStatement: public ConnectionStatement {
public:
	InterConnectionStatement(string sc, string sp);
	virtual ~InterConnectionStatement();
	virtual string toString(int n = 0);
private:
	string sourceCircuitId;
	string sourcePortId;
};

} /* namespace CodeWriter */


/******************************************************************************************
*class OutputConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

class OutputConnectionStatement: public ConnectionStatement {
public:
	OutputConnectionStatement(string op);
	//virtual ~OutputConnectionStatement();
	virtual string toString(int n = 0);
private:
	string outputPortId;
};
}

/******************************************************************************************
*class InputConnectionStatement
*******************************************************************************************/
namespace CodeWriter {

class InputConnectionStatement: public ConnectionStatement {
public:
	InputConnectionStatement(string ip);
	virtual ~InputConnectionStatement();
	virtual string toString(int n = 0);
private:
	string inputPortId;
};

} /* namespace CodeWriter */

/******************************************************************************************
*class GarbledClassFunction
*******************************************************************************************/
namespace CodeWriter {

class GarbledClassFunction: public Statement {
public:
	virtual string toString(int n = 0);
	GarbledClassFunction(string cn, vector<string> as, string in, string out, string component);
private:
	string className;
	vector<string> arguments;
	string indegree;
	string outdegree;
	string componentNum;
private:
	string declareVariable(int n = 0);
	string declareConstruction(int n =0);
};

} /* namespace CodeWriter */


#endif 
