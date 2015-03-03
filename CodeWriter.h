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
	virtual string toString() = 0;
	virtual void insertDesCircuit(string str);
	virtual void insertDesInport(string str);
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
	virtual string toString()=0;
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
	void insert(Statement* s);
	string toString();
	virtual void insertDesCircuit(string str);
	virtual void insertDesInport(string str);
private:
	string startIndex;
	string endIndex;
	string step;
	string variable;
	vector<Statement* > statements;
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
	virtual string toString();
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
	virtual string toString();
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
	virtual string toString();
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
	virtual string toString();
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
	virtual string toString();
private:
	string inputPortId;
};

} /* namespace CodeWriter */


#endif 
