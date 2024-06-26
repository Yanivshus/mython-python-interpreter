#include "Type.h"
#include "IndentationException.h"
#include "NameErrorException.h"
#include "Parser.h"
#include <iostream>

#define WELCOME "Welcome to Magshimim Python Interperter version 1.0 by "
#define YOUR_NAME "Yaniv"


int main(int argc,char **argv)
{
	std::cout << WELCOME << YOUR_NAME << std::endl;

	std::string input_string;

	// get new command from user
	std::cout << ">>> ";
	std::getline(std::cin, input_string);
	
	while (input_string != "quit()")
	{
		try
		{
			// parsing command
			Parser::parseString(input_string);
		}
		catch (IndentationException err) {
			std::cout << err.what() << std::endl;
		}
		catch (SyntaxException err1) {
			std::cout << err1.what() << std::endl;
		}
		catch (NameErrorException err2) {
			std::cout << err2.what() << std::endl;
		}


		// get new command from user
		std::cout << ">>> ";
		std::getline(std::cin, input_string);
	}
	Parser::cleanVers();
	return 0;
}
