#include "interpreter.h"

Interpreter::Interpreter(){
}
Interpreter::Interpreter(const Parser parser):parser(parser)
{
}
Interpreter::~Interpreter()
{
}
int Interpreter::interpret()
{
	AST* tree = parser.parser();
	return -1; 
}
