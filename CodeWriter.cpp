#include "stdafx.h"
#include "CodeWriter.h"


/******************************************************************************************
*class BinaryLinearEquation
*******************************************************************************************/
namespace CodeWriter {

BinaryLinearEquation::BinaryLinearEquation() {
	// TODO Auto-generated constructor stub

}

BinaryLinearEquation::~BinaryLinearEquation() {
	// TODO Auto-generated destructor stub
}

string BinaryLinearEquation::toString()
{
	return "";
}
} /* namespace CodeWriter */


/******************************************************************************************
*class BracketStatement
*******************************************************************************************/
namespace CodeWriter {

BracketStatement::BracketStatement() {
	// TODO Auto-generated constructor stub

}

BracketStatement::~BracketStatement() {
	// TODO Auto-generated destructor stub
}

string BracketStatement::toString()
{
	return "";
}
} /* namespace CodeWriter */

/******************************************************************************************
*class Expression
*******************************************************************************************/
namespace CodeWriter {

Expression::Expression() {
	// TODO Auto-generated constructor stub

}

Expression::~Expression() {
	// TODO Auto-generated destructor stub
}
/*
string Expression::toString()
{
	return "";
}
*/
Statement* Expression::generateStatement(CodeGenerator::CodeGenerator* cg)
{
	//if it is Initialtor
	
}
} /* namespace CodeWriter */

/******************************************************************************************
*class ForLoopStatement
*******************************************************************************************/
namespace CodeWriter {

ForLoopStatement::ForLoopStatement() {
	// TODO Auto-generated constructor stub

}

ForLoopStatement::~ForLoopStatement() {
	// TODO Auto-generated destructor stub
}

string ForLoopStatement:: toString(){
	string content = "";
	content += "for(";
	content += assignment->toString()+"; ";
	content += condition->toString()+"; ";
	content += updation->toString()+")\n";
	content += loopContent->toString();
	return content;
}

ForLoopStatement::ForLoopStatement(BinaryLinearEquation* assignment, BinaryLinearEquation* condition,
			BinaryLinearEquation* updation, BracketStatement* loopContent)
{
	this->assignment = assignment;
	this->condition = condition;
	this->updation = updation;
	this->loopContent = loopContent;
}
} /* namespace CodeWriter */


/******************************************************************************************
*class FunctionEquation
*******************************************************************************************/
namespace CodeWriter {
using namespace std;
FunctionEquation::FunctionEquation() {
	// TODO Auto-generated constructor stub

}

FunctionEquation::~FunctionEquation() {
	// TODO Auto-generated destructor stub
}

FunctionEquation::FunctionEquation(Variable* caller, Variable* functionName, vector<Variable*> parameters)
{
	this->caller = caller;
	this->functionName = functionName;
	this->parameters = parameters;
}

string FunctionEquation::toString()
{
	string content = "";
	if(!caller->isEmpty())
		content += caller->toString()+".";
	content += functionName->toString()+"(";
	for(auto it=parameters.begin();it!=parameters.end(); it++)
	{
		content += (*it)->toString()+", ";
	}
	int size = content.size();
	content = content.substr(0, size-2)+")";
	return content;
}

} /* namespace CodeWriter */
/******************************************************************************************
*class Statement
*******************************************************************************************/
namespace CodeWriter {

Statement::Statement() {
	// TODO Auto-generated constructor stub

}

Statement::~Statement() {
	// TODO Auto-generated destructor stub
}

string Statement::toString()
{
	return "";
}

Statement* Statement::generateStatement(CodeGenerator::CodeGenerator* cg)
{
	if(cg->isSingle())
		return new Expression(cg);
	else
		return new ForLoopStatement(cg);
}
} /* namespace CodeWriter */


/******************************************************************************************
*class Variable
*******************************************************************************************/
namespace CodeWriter {

Variable::Variable() {
	// TODO Auto-generated constructor stub

}

Variable::~Variable() {
	// TODO Auto-generated destructor stub
}

Variable::Variable(string content)
{
	this->variableContent = content;
}
string Variable::toString()
{
	return this->variableContent;
}

bool Variable::isEmpty()
{
	return this->variableContent.empty();
}

Variable::Variable(FunctionEquation fq)
{
	Variable(fq.toString());
}

} /* namespace CodeWriter */
