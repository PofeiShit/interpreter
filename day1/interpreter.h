#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include "token.h"
#include <stdio.h>
class Interpreter
{
	public:
		std::string text;
		size_t pos;
		Token current_token;

	public:
		Interpreter(){}
		Interpreter(const std::string &_text):text(_text), pos(0){
			current_token = Token();
		}
		Token get_next_token();
		void eat(const std::string &token_type);
		int expr();	
		void error();
};

#endif
