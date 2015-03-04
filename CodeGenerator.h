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
class GarbledClass;
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
		virtual string toString(int n = 0);
		friend Range* getRange(string range);
		virtual ~CodeGenerator();
	protected:
		Statement* s;
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
		string portIndex;
	public:
		Statement * generateStatement();
		virtual Statement* getStatement() = 0;
		virtual string getCircuitVariable() = 0;
		virtual string getPortVariable() = 0;
		Component(string pi);
	private:
		virtual ForLoopStatement* getForLoopStatement(string variable) = 0;
		ForLoopStatement* generateForLoopStatement();
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
		virtual Statement* getStatement();
		SingleComponent(string ci, string si, string port);
		string getCircuitVariable();
		string getPortVariable();
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
		virtual Statement* getStatement();
		string getCircuitVariable();
		string getPortVariable();
		MultipleComponent(string ci, string port);
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
		Input(string ip, string port);
		virtual Statement* getStatement();
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
		Output(string ip, string port);
		virtual Statement* getStatement();
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
	
	public:
		Connection(Component* sc, Component* dc);
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
		InputConnection(string inputStartIndex, string sc, Component* endpoint);
	
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
		OutputConnection(string inputStartIndex, string sc, Component* endpoint);
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
		string step;
		string num;
	public:
		MultipleRange(string str);
		string getVariable();
		string getVariable(string str);
		string getNum();
	};
}

/******************************************************************************************
GarbledClass
*******************************************************************************************/
namespace CodeGenerator
{
	class GarbledClass : public CodeGenerator
	{
	private:
		string className;
		string arguments;
		string inDegree;
		string outDegree;
		string componentNum;
	public:
		GarbledClass(string cn, string as, string in, string out, string component);
		virtual void setStatement();
		string getClassName();
	};
}
#endif  /*  end codegenerator.h file  */