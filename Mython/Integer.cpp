#include "Integer.h"

Integer::Integer(const int val) : Type(true)
{
	this->_value = val;
}

Integer::~Integer()
{
}

bool Integer::isPrintable() const
{
	return true;
}

std::string Integer::toString() const
{
	return std::to_string(this->_value);
}
