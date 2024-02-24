#pragma once
#include "Type.h"

class Void : public Type {
private:
	
public:
	Void();
	~Void();
	//check if a type is printable.
	virtual bool isPrintable() const override;

	//turns type to string and returns it.
	virtual std::string toString() const override;
};