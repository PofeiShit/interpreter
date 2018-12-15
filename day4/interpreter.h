#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "token.h"
#include "lexer.h"
class Interpreter
{
	public:
		Token current_token;
		Lexer lexer;

	public:
		Interpreter();
		Interpreter(const Lexer _lexer);
		void eat(const std::string &token_type);
		void error();
		int expr();	
		int factor();
};

#endif
