#include "Parser.h"
#include "IndentationException.h"
#include "NameErrorException.h"
#include <iostream>
#include <string>
#include <algorithm>

// declaring static map.
std::unordered_map<std::string, Type*> Parser::_veriables;

Type* Parser::parseString(std::string str)
{
	if (str.length() > 0)
	{
		if (str.front() == '	' || str.front() == ' ') 
		{
			throw IndentationException();
		}
		else
		{
			Helper::trim(str);
			try {
				bool isAssignable = makeAssignment(str);
				if (getVariableValue(str) != nullptr) // check if the veriable already exists so we will print it.
				{
					std::cout << getVariableValue(str)->toString() << std:: endl;
				}
				else if (isAssignable == false) // if the assigment doesnt work that means its not a veriable assaigment.
				{
					Type* line = getType(str);
					if (line == nullptr) // if the line created that means its a valid value.
					{
						throw(SyntaxException());
					}
					std::cout << line->toString() << std::endl;
					delete line;
				}
			}
			catch (IndentationException e1) {
				throw e1;
			}
			catch(NameErrorException e2){
				throw e2;
			}

		}
		
	}

	return nullptr;
}

Type* Parser::getType(std::string str)
{
	if (Helper::isInteger(str) == true)//check if it is integer
	{
		return new Integer(std::atoi(str.c_str()));
	}
	else if (Helper::isBoolean(str) == true) //check if it is a bool
	{
		if (str == "True")
		{
			return new Boolean(true);
		}
		else
		{
			return new Boolean(false);
		}
	}
	else if (Helper::isString(str) == true) // check if it is a string.
	{
		return new String(str);
	}
	else if (Helper::isList(str) == true) {
		try
		{
			return parseList(str);
		}
		catch (...)
		{
			return nullptr;
		}
	}
	else
	{
		return nullptr;
	}
}



void Parser::cleanVers()
{
	for (auto i = _veriables.begin(); i != _veriables.end(); )
	{
		delete (*i).second;// deleting each element from the map.
		i = _veriables.erase(i);
	}
}

bool Parser::isLegalVarName(std::string str)
{
	if (Helper::isDigit(str.front())) 
	{ 
		return false;
	}
	for (auto i = str.begin(); i != str.end(); i++)
	{	
		bool returnType = true;
		char curr = (*i);
		//checking if a charecter is valid.
		if (Helper::isUnderscore(curr) == true) {
			returnType = false;
		}
		else if (Helper::isDigit(curr) == true) {
			returnType = false;
		}
		else if(Helper::isLetter(curr) == true) {
			returnType = false;
		}
		if (returnType == true) {
			return false;
		}
	}
	return true;
}

bool Parser::makeAssignment(std::string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '=') {
			count++;
		}
	}
	if (count != 1) {
		return false;
	}
	auto index = str.find("=");
	//parsing the line
	std::string verName = str.substr(0, index);//ver name
	std::string verData = str.substr(index + 1, str.size() - index + 1);//the data assigned.

	// triming spaces.
	Helper::trim(verData);
	Helper::trim(verName);

	if (isLegalVarName(verName) == false) //checking if the varName is legal.
	{
		throw NameErrorException(verName);
	}

	Type* ver = nullptr;
	Type* isVeriable = getVariableValue(verData);

	if (isVeriable != nullptr) // checking if the veriable data is a existing veriable, if yes we will deep copy its value.
	{
		ver = getType(isVeriable->toString());
	}
	else 
	{// if the data isnt a veriable we will just, assign it regularly.
		ver = getType(verData);
		if (ver == nullptr) {
			throw SyntaxException();
		}
	}

	delete _veriables[verName];// deleting former memory so there wont be memory leak.
	_veriables[verName] = ver;
	return true;
}

Type* Parser::getVariableValue(std::string str)
{
	auto isFound = _veriables.find(str);
	if (isFound == _veriables.end()) {//check if the str name exists.
		return nullptr;
	}
	return _veriables[str];
}

List* Parser::parseList(std::string str)
{
	List* newObList = new List(false);
	std::string toParse = str.substr(1, str.size() - 2);
	std::vector<std::string> res;
	size_t pos = 0;

	while (pos < toParse.size()) 
	{
		// Find the position of the comma
		size_t found = toParse.find(",", pos);

		// Check if the delimiter is found
		if (found != std::string::npos) {
			std::string newVer = toParse.substr(pos, found - pos);
			Helper::trim(newVer);
			res.push_back(newVer);

			// Move the position after the delimiter
			pos = found + 1;
		}
		else {
			// If no more delimiters are found, process the remaining part
			std::string newVer = toParse.substr(pos);
			Helper::trim(newVer);
			res.push_back(newVer);

			// Exit the loop
			break;
		}
	}


	for (int i = 0; i < res.size(); i++)
	{
		newObList->_seq.push_back(getType(res[i]));
		if (newObList->_seq[i] == nullptr) {
			throw SyntaxException();
		}
	}

	return newObList;

}


