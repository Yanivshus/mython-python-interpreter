#pragma once
#include "Type.h"
#include <vector>

class Sequence : public Type
{
private:
	
public:
	Sequence(const bool isTemp);
	~Sequence();
	//check if a type is printable.
	virtual bool isPrintable() const = 0;

	//turns type to string and returns it.
	virtual std::string toString() const = 0;
};