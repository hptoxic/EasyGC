#include "stdafx.h"
#include "JavaClass.h"
using namespace std;
using namespace CodeGenerator;
/*************************************************************************************
JavaClass
**************************************************************************************/
namespace JavaClass
{
	JavaClass::JavaClass(GarbledClass _gc, 
						vector<Initialtor> _init,
						vector<Connection> _inter, 
						vector<InputConnection> _input,
						vector<OutputConnection> _output,
						vector<FixedWire> _fw):gc(_gc), init(_init),inter(_inter), input(_input), 
												output(_output), fw(_fw)
	{};

		
	string JavaClass::getFileContent()
	{
		string output = "";
		//file header
		output += getHeader();
		output += "{\n";
		output += getConstructor();
		output += getConnectWires(1);
		output += getDefineOutput(1);
		output += getFixedWire(1);
		output += "}\n";
		return output;
	}

	string JavaClass::getHeader(int n)
	{
		string indent(n, '\t');
		string output = "";
		output += indent+"package YaoGC;\n";
		output += indent+"public class "+gc.getClassName()+" extends CompositeCircuit\n";
		return output;
	}

	string JavaClass::getConstructor(int n)
	{
		gc.setStatement();
		return gc.toString(n+1);
	}

	string JavaClass::getCreateSubCircuit(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void createSubCircuits() throws Exception \n"+indent+"{\n";
		for(auto it=init.begin(); it!=init.end(); it++)
		{
			it->setStatement();
			output += it->toString(n+1);
		}
		output += indent+"}\n";
		return output;
	}

	string JavaClass::getConnectWires(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void connectWires() \n"+indent+"{\n";
		for(auto it=input.begin(); it!=input.end(); it++)
		{
			it->setStatement();
			output += it->toString(n+1);
		}

		for(auto it=inter.begin(); it!=inter.end(); it++)
		{
			it->setStatement();
			output += it->toString(n+1);
		}

		output += indent+"}\n";
		return output;
	}

	string JavaClass::getDefineOutput(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void defineOutputWires() \n"+indent+"{\n";
		for(auto it=this->output.begin(); it!=this->output.end(); it++)
		{
			it->setStatement();
			output += it->toString(n+1);
		}

		output += indent+"}\n";
		return output;
	}

	string JavaClass::getFixedWire(int n)
	{
		string indent(n, '\t');
		string output = indent+"protected void fixInternalWires() \n"+indent+"{\n";
		for(auto it=this->fw.begin(); it!=this->fw.end(); it++)
		{
			it->setStatement();
			output += it->toString(n+1);
		}

		output += indent+"}\n";
		return output;
	}


	void JavaClass::insert(Initialtor i)
	{
		this->init.push_back(i);
	}
	void JavaClass::insert(Connection c)
	{
		this->inter.push_back(c);
	}
	void JavaClass::insert(InputConnection ic)
	{
		this->input.push_back(ic);
	}
	void JavaClass::insert(OutputConnection oc)
	{
		this->output.push_back(oc);
	}
	void JavaClass::insert(FixedWire f)
	{
		this->fw.push_back(f);
	}

	JavaClass::JavaClass(GarbledClass _gc):gc(_gc)
	{}
}
