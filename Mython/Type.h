#pragma once
#include <iostream>


class Type
{
private:
	bool _isTemp;
public:
	Type(const bool isTemp);
	~Type();

	bool getIsTemp() const;
	void setIsTemp(bool isTemp);

	//check if a type is printable.
	virtual bool isPrintable() const = 0;

	//turns type to string and returns it.
	virtual std::string toString() const = 0;
};
