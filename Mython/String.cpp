#include "String.h"


String::String(const std::string& val) : Type(true)
{
	this->_value = val;
}

String::~String()
{
}

bool String::isPrintable() const
{
	return true;
}

std::string String::toString() const
{
	std::string toReturn = "";
	if (this->_value.front() != '\'') 
	{
		//changing the string so it would start with ' and end with ';
		toReturn.push_back('\'');
		std::string curr = this->_value;
		curr.pop_back();
		curr.erase(0, 1);
		for (int i = 0; i < curr.size(); i++)//parsing the string.
		{
			if (curr[i] == '\'') 
			{
				toReturn += "\"";
			}
			else {
				toReturn += curr[i];
			}
		}
		toReturn.push_back('\'');// adding ' in the end.
		return toReturn;
	}
	else 
	{
		return this->_value;
	}

}
