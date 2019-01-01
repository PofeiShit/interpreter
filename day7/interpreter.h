#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "parser.h"
class Interpreter
{
	public:
		Parser parser;

	public:
		Interpreter();
		Interpreter(const Parser parser);
		~Interpreter();

		int visitBinOp(BinOp* node);
		int interpret();
};
#endif
