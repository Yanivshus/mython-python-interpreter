#pragma once
#include "Sequence.h"

class List : public Sequence {
public:
	std::vector<Type*> _seq;
	List(bool isTmp);
	~List();

	virtual bool isPrintable() const override;
	virtual std::string toString() const override;
};