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
		//checking for tab or space in the start.
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
				else if(Helper::isType(str) == true)//checking if the function type is called.
				{
					std::cout << getTypeOfValue(str) << std::endl;
				}
				else if (isAssignable == false) // if the assigment doesnt work that means its not a veriable assaigment.
				{
					Type* line = getType(str);
					if (line == nullptr) // if the line created that means its a valid value.
					{
						throw(NameErrorException(str));
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
			catch (SyntaxException e3) {
				throw e3;
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
	int isList = 0;

	if (isVeriable != nullptr) // checking if the veriable data is a existing veriable, if yes we will deep copy its value.
	{
		//checking if the valuue is a list.
		if (isVeriable->toString()[isVeriable->toString().size()-1] == ']'
			&& isVeriable->toString()[0] == '[')
		{
			_veriables[verName] = isVeriable;// if its a list we will do a pointer assigning to the same ver.
			isList = 1;
		}
		else {
			ver = getType(isVeriable->toString());
		}
	}
	else 
	{// if the data isnt a veriable we will just, assign it regularly.
		ver = getType(verData);
		if (ver == nullptr) {
			throw NameErrorException(verData);
		}
	}

	if (isList == 0) {
		delete _veriables[verName];// deleting former memory so there wont be memory leak.
		_veriables[verName] = ver;
	}
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

std::string Parser::getTypeOfValue(const std::string& str)
{
	std::string value = "";
	// Find the position of the opening and closing parentheses
	size_t openParenPos = str.find('(');
	size_t closeParenPos = str.find(')');

	// Create a substring before the "type()" part
	value = str.substr(openParenPos + 1, closeParenPos - openParenPos - 1);

	





	//checking for the value what is type
	if (Helper::isInteger(value) == true) {
		return "<type 'int'>";
	}
	else if (Helper::isBoolean(value) == true) {
		return "<type 'bool'>";
	}	
	else if (Helper::isString(value) == true) {
		return "<type 'str'>";
	}	
	else if (Helper::isList(value) == true) {
		return "<type 'list'>";
	}
	else {// if any of the type are suitable then its a veriable.
		Type* valueOfVer = getVariableValue(value);
		if (valueOfVer == nullptr) {// if not a veriable then it doesnt exists.
			throw(NameErrorException(value));
		}
		else {
			if (Helper::isInteger(valueOfVer->toString()) == true) {
				return "<type 'int'>";
			}
			else if (Helper::isBoolean(valueOfVer->toString()) == true) {
				return "<type 'bool'>";
			}
			else if (Helper::isString(valueOfVer->toString()) == true) {
				return "<type 'str'>";
			}
			else if (Helper::isList(valueOfVer->toString()) == true) {
				return "<type 'list'>";
			}
			else {
				return "idk";
			}
		}
	}

}


