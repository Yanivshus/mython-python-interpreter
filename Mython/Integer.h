#pragma once
#include "Type.h"
#include <string>

class Integer : public Type {
private:
	int _value;
public:
	Integer(const int val);
	~Integer();
	//int is alwayes printable so true will be returned.
	virtual bool isPrintable() const override;

	//returns the value as string.
	virtual std::string toString() const override;
};


