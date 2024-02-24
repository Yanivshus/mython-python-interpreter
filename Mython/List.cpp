#include "List.h"

List::List(const std::string& str, bool isTmp) : Sequence(isTmp)
{
	
}

List::~List()
{
}

bool List::isPrintable() const
{
	return false;
}

std::string List::toString() const
{
	return std::string();
}
