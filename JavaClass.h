#ifndef JAVACLASS_H_
#define JAVACLASS_H_
#include <string>
#include<vector>
#include "CodeGenerator.h"
using namespace std;
using namespace CodeGenerator;
/*************************************************************************************
JavaClass
**************************************************************************************/
namespace JavaClass
{
	class JavaClass
	{
	private:
		GarbledClass gc;
		vector<Initialtor> init;
		vector<Connection> inter;
		vector<InputConnection> input;
		vector<OutputConnection> output;
		vector<FixedWire> fw;
	public:
		JavaClass(GarbledClass _gc, 
						vector<Initialtor> _init,
						vector<Connection> _inter, 
						vector<InputConnection> _input,
						vector<OutputConnection> _output,
						vector<FixedWire> _fw);
		JavaClass(GarbledClass _gc);
		string getFileContent();
		void insert(Initialtor i);
		void insert(Connection c);
		void insert(InputConnection ic);
		void insert(OutputConnection);
		void insert(FixedWire f);
	private:
		string getHeader(int n = 0);
		string getConstructor(int n = 0);
		string getCreateSubCircuit(int n = 0);
		string getConnectWires(int n = 0);
		string getDefineOutput(int n = 0);
		string getFixedWire(int n = 0);

	};
}

#endif