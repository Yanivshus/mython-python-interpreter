#pragma once
#include "Sequence.h"
class List : public Sequence {
private:
	std::vector<Type*> _seq;
public:
	List(const std::string& str, bool isTmp);
	~List();

	virtual bool isPrintable() const;
	virtual std::string toString() const;
};