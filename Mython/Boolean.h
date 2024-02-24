#pragma once
#include "Type.h"
#include <string>

class Boolean : public Type {
private:
	bool _value;

public:
	Boolean(const bool val);
	~Boolean();

	//check if a type is printable.
	virtual bool isPrintable() const override;

	//turns bool to string and returns it.
	virtual std::string toString() const override;
};
