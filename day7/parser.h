#ifndef PARSER_H_
#define PARSER_H_
#include "token.h"
#include "lexer.h"
#include "binoperator.h"
#include "num.h"
class Parser 
{
	public:
		Token current_token;
		Lexer lexer;

	public:
		Parser();
		Parser(const Lexer _lexer);
		void eat(const std::string &token_type);
		void error();
		AST* expr();	
		AST* factor();
		AST* term();
		AST* parser();
};

#endif
