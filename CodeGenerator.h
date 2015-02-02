namespace CodeGenerator
{
class CodeGenerator;
class Initialtor;
class Component;
class SingleComponent;
class MultipleComponent;
class Connection;
class Range;
}
#ifndef CODEGENERATOR_H_
#define CODEGENERATOR_H_
#include <string>
#include <vector>
#include "CodeWriter.h"
using namespace std;
using namespace CodeWriter;


namespace CodeGenerator
{
	class CodeGenerator
	{
	public:
		virtual void setStatement() = 0;
	protected:
		Statement* s;
	};
}

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
		Initialtor(string ci, string arg);
		friend Range* getRange(string range);
		void setStatement();
	};
}


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
		bool checkValidity();
		void setStatement();
	};
}

namespace CodeGenerator
{
	class Component
	{
	protected:
		int dimension;
		string portIndexRange;
	
	public:
		int getDimension();
	};
}


namespace CodeGenerator
{
	class SingleComponent : public Component
	{
	protected:
		string startIndexRange;
	private:
		string circuitIndex;
	};
}


namespace CodeGenerator
{
	class MultipleComponent : public Component
	{
	private:
		string circuitIndexes;
	};
}

namespace CodeGenerator
{
	class Range
	{
	public:
		virtual void setContent(Statement*) = 0;
	};
}

namespace CodeGenerator
{
	class SingleRange : public Range
	{
	private:
		string index;
	public:
		void setContent(Statement*);
		SingleRange(string str);
	};
}
namespace CodeGenerator
{
	class MultipleRange : public Range
	{
	private:
		string startIndex;
		string endIndex;
		string step;
		string num;
	public:
		void setContent(Statement*);
		MultipleRange(string str);
	};
}
#endif  /*  end codegenerator.h file  */