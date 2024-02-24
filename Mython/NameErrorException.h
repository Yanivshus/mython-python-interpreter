#pragma once
#include "InterpreterException.h"
#include <iostream>

class NameErrorException : public InterpreterException
{
public:
	std::string _err;
	NameErrorException(std::string name);
	virtual const char* what() const noexcept;
};

