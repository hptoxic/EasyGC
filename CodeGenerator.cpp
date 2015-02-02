#include "stdafx.h"
#include "CodeGenerator.h"

namespace CodeGenerator
{
Initialtor::Initialtor()
{
}
Initialtor::Initialtor(string ci, string arg)
{
	this->circuitIndexes = ci;
	this->arguments = arg;
}
void Initialtor:: setStatement()
{
	Range *index = getRange(circuitIndexes);

};

Range* getRange(string range)
{
	//judge whether it is multiple or single
	if(find(range.begin(),range.end(),':')==range.end())
		return new SingleRange(range);
	else
		return new MultipleRange(range);
}

}


namespace CodeGenerator
{
	SingleRange::SingleRange(string str)
	{
		this->index = str.substr(1, str.length()-2);
	}
	void SingleRange::setContent(Statement *s)
	{
	}
}