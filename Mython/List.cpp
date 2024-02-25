#include "List.h"
#include "Helper.h"
#include "SyntaxException.h"

List::List(bool isTmp) :Sequence(isTmp)
{

}

List::~List()
{
	for (int i = 0; i < this->_seq.size(); i++)
	{
		delete this->_seq[i];
	}
}

bool List::isPrintable() const
{
	return true;
}

std::string List::toString() const
{
	std::string str = "[";
	for (int i = 0; i < this->_seq.size(); i++)
	{
		str+=this->_seq[i]->toString();
		str += ", ";
	}
	// removing trailin ', '
	if (str[str.size() - 1] == ' ' || str[str.size() - 2] == ',') {
		str.pop_back();
		str.pop_back();
	}
	str += "]";
	return str;
}
