#include "NameErrorException.h"
#include <string>

NameErrorException::NameErrorException(std::string name)
{
	this->_err = "NameError : name " + name + " is not defined or not valid";
}

const char* NameErrorException::what() const noexcept
{
	return this->_err.c_str();
}