#include "Type.h"

Type::Type(const bool isTemp)
{
	this->_isTemp = isTemp;
}

Type::~Type()
{
}

bool Type::getIsTemp() const
{
	return this->_isTemp;
}

void Type::setIsTemp(bool isTemp)
{
	this->_isTemp = isTemp;
}
