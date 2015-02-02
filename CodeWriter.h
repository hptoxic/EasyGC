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
class BinaBinaryLinearEquation;
class Expression;
class Variable;
class Statement;
class FunctionEquation;
}
#include "CodeGenerator.h"

/******************************************************************************************
*class Statement
*******************************************************************************************/
namespace CodeWriter {

class Statement {
public:
	Statement();
	virtual ~Statement();
	virtual string toString();
	virtual Statement* generateStatement(CodeGenerator::CodeGenerator* cg);
	//string toString();
};

} /* namespace CodeWriter */

/******************************************************************************************
*class Expression
*******************************************************************************************/
namespace CodeWriter {

class Expression: public Statement {
public:
	Expression();
	virtual ~Expression();
	virtual string toString();
	virtual Statement* generateStatement(CodeGenerator::CodeGenerator* cg);
};

} /* namespace CodeWriter */


/******************************************************************************************
*class Variable
*******************************************************************************************/
namespace CodeWriter {

class Variable: public Expression {
public:
	Variable();
	Variable(string content);
	virtual ~Variable();
	string toString();
	Variable(FunctionEquation fq);
	bool isEmpty();
private:
	string variableContent;
};
}


/******************************************************************************************
*class BinaryLinearEquation
*******************************************************************************************/
namespace CodeWriter {
class BinaryLinearEquation: public Expression {
public:
	BinaryLinearEquation();
	virtual ~BinaryLinearEquation();
	string toString();
private:
	Expression *leftExpression;
	Expression *rightExpression;
	Variable *operand;
};

} /* namespace CodeWriter */

/******************************************************************************************
*class BracketStatement
*******************************************************************************************/
namespace CodeWriter {

class BracketStatement: public Statement {
public:
	BracketStatement();
	virtual ~BracketStatement();
	string toString();
private:
	vector<Statement*> statements;
};

} /* namespace CodeWriter */


/******************************************************************************************
*class ForLoopStatement
*******************************************************************************************/

namespace CodeWriter {
class ForLoopStatement: public Statement {
public:
	ForLoopStatement();
	virtual ~ForLoopStatement();
	ForLoopStatement(BinaryLinearEquation* assignment, BinaryLinearEquation* condition,
			BinaryLinearEquation* updation, BracketStatement* loopContent);
	string toString();
private:
	BinaryLinearEquation* assignment;
	BinaryLinearEquation* condition;
	BinaryLinearEquation* updation;
	BracketStatement* loopContent;
};

} /* namespace CodeWriter */


/******************************************************************************************
*class FunctionEquation
*******************************************************************************************/
namespace CodeWriter {


class FunctionEquation: public Expression {
public:
	FunctionEquation();
	virtual ~FunctionEquation();
	string toString();
	FunctionEquation(Variable* caller, Variable* functionName, vector<Variable*> parameters);
private:
	Variable* caller;
	Variable* functionName;
	vector<Variable*> parameters;
};

} /* namespace CodeWriter */


#endif 
