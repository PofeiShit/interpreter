#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
class Interpreter
{
	public:
		std::string text;
		size_t pos;
		Token current_token;
		char current_char;
	public:
		Interpreter(){}
		Interpreter(const std::string &_text):text(_text), pos(0){
			current_token = Token();
			current_char = text[pos];
		}

		Token get_next_token();
		void eat(const std::string &token_type);
		int expr();	
		int term();
		void error();
		void skip_whitespace();
		std::string integer();
		void advance();
};

#endif
