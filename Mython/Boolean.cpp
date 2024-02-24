#include "Boolean.h"

Boolean::Boolean(const bool val) : Type(true)
{
	this->_value = val;
}

Boolean::~Boolean()
{
}

bool Boolean::isPrintable() const
{
	return true;
}

std::string Boolean::toString() const
{
	if (this->_value == true) 
	{
		return "True";
	}
	return "False";
}
