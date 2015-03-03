namespace CodeGenerator
{
class CodeGenerator;
class Initialtor;
class FixedWire;
class Component;
class SingleComponent;
class Input;
class Output;
class MultipleComponent;
class Connection;
class InterConnection;
class InputConnection;
class OutputConnection;
class Range;
}
#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_
#include <string>
#include <vector>
#include "CodeWriter.h"
using namespace std;
using namespace CodeWriter;

/******************************************************************************************
CodeGenerator
*******************************************************************************************/
namespace CodeGenerator
{
	class CodeGenerator
	{
	public:
		virtual void setStatement() = 0;
		virtual void printStatement();
		friend Range* getRange(string range);
	protected:
		vector<Statement*> s;
	};
}
/******************************************************************************************
Initialtor
*******************************************************************************************/
namespace CodeGenerator
{
	class Initialtor : public CodeGenerator
	{
	private:
		string className;
		string circuitIndexes;
		string arguments;
		bool single;
	public:
		Initialtor();
		~Initialtor();
		Initialtor(string ci, string arg, string className);
		void setStatement();
	private:
		Statement *generateStatement(Range* cir, vector<Range* > pir);
	};
}

/******************************************************************************************
FixedWire
*******************************************************************************************/
namespace CodeGenerator
{
	class FixedWire : public CodeGenerator
	{
	private:
		string circuitIndexes;
		string portStartIndex;
		string portIndexes;
		string value;
	public:
		FixedWire(string ci, string psi, string pi, string v);
		virtual void setStatement();

	};
}

/******************************************************************************************
Component
*******************************************************************************************/
namespace CodeGenerator
{
	class Component
	{
	protected:
	
	public:
		virtual Statement* getStatement(string ip) = 0;
		virtual string getCircuitVariable() = 0;
		virtual string getPortVariable(string srcPort) = 0;
	private:
		virtual ForLoopStatement* getForLoopStatement(string variable) = 0;
	};
}

/******************************************************************************************
SingleComponent
*******************************************************************************************/
namespace CodeGenerator
{
	class SingleComponent : public Component
	{
	protected:
		string startIndexRange;
	private:
		string circuitIndex;
	public:
		virtual Statement* getStatement(string ip);
		SingleComponent(string si, string ci);
		string getCircuitVariable();
		string getPortVariable(string srcPort);
	private:
		virtual ForLoopStatement* getForLoopStatement(string variable);
	};
}

/******************************************************************************************
MultipleComponent
*******************************************************************************************/
namespace CodeGenerator
{
	class MultipleComponent : public Component
	{
	private:
		string circuitIndexes;
	public:
		virtual Statement* getStatement(string ip);
		string getCircuitVariable();
		string getPortVariable(string srcPort);
		MultipleComponent(string ci);
	private:
		virtual ForLoopStatement* getForLoopStatement(string variable);
	};
}


/******************************************************************************************
Input
*******************************************************************************************/
namespace CodeGenerator
{
	class Input : public SingleComponent
	{
	public:
		Input(string ip);
		virtual Statement* getStatement(string ip);
	};
}
/******************************************************************************************
Output
*******************************************************************************************/
namespace CodeGenerator
{
	class Output : public SingleComponent
	{
	public:
		Output(string ip);
		virtual Statement* getStatement(string ip);
	};
}

/******************************************************************************************
Connection
*******************************************************************************************/
namespace CodeGenerator
{
	class Connection : public CodeGenerator
	{
	private:
		//a input [0:1:2L], startIndex[0:1:2]
		Component* sourceCircuit;
		//multiple 2
		Component* destinationCircuit;
	
		//[0:1:L]
		string srcPortIndex;
		//[0:1:L]
		string dstPortIndex;
	public:
		Connection(string sp, string dp,Component* sc, Component* dc);
		void setStatement();
	};
}

/******************************************************************************************
InputConnection
*******************************************************************************************/
namespace CodeGenerator
{
	class InputConnection : public Connection
	{
	public:
		InputConnection(string inputStartIndex, Component* endpoint, string sc, string rc);
	
	};
}

/******************************************************************************************
OutputConnection
*******************************************************************************************/
namespace CodeGenerator
{
	class OutputConnection : public Connection
	{
	public:
		OutputConnection(string inputStartIndex, Component* endpoint, string sc, string rc);
	};
}

/******************************************************************************************
Range
*******************************************************************************************/
//to seperate range use ;
//in a range, use , particularly within parameter list
namespace CodeGenerator
{
	class Range
	{
	protected:
		bool multiple;
	public:
		bool isMultiple();
		static vector<vector<Range* > > getComboRanges(string str);
		static vector<Range* > getRanges(string str);
		virtual string getVariable();
		virtual string getVariable(string variable);
		virtual string getNum();

		static Range* getRange(string str);
		static vector<Range* > getComboRange(string str);
	};
}
/******************************************************************************************
SingleRange
*******************************************************************************************/
namespace CodeGenerator
{
	class SingleRange : public Range
	{
	private:
		string index;
	public:
		SingleRange(string str);
		string getVariable();
		string getVariable(string str);
	};
}

/******************************************************************************************
MultipleRange
*******************************************************************************************/
namespace CodeGenerator
{
	class MultipleRange : public Range
	{
	private:
		string startIndex;
		string endIndex;
		string step;
	public:
		MultipleRange(string str);
		string getVariable();
		string getVariable(string str);
		string getNum();
	};
}
#endif  /*  end codegenerator.h file  */