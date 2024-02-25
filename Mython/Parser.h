#pragma once
#include "InterpreterException.h"
#include "Type.h"
#include "Helper.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include "Boolean.h"
#include "Integer.h"
#include "String.h"
#include "SyntaxException.h"
#include "List.h"

class Parser
{
public:
    static Type* parseString(std::string str);
    static Type* getType(std::string str);
    static std::unordered_map<std::string, Type*> _veriables;
    static void cleanVers();
private:
    static bool isLegalVarName(std::string str);
    static bool makeAssignment(std::string str);
    static Type* getVariableValue(std::string str);
    static List* parseList(std::string str);
    

};
