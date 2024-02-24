#pragma once
#include "Type.h"


class String : public Type{
private:
	std::string _value;
public:
	String(const std::string& val);
	~String();



	//check if a type is printable.
	virtual bool isPrintable() const override;

	//turns type to string and returns it.
	virtual std::string toString() const override;
};
