#ifndef PARSER_H_
#define PARSER_H_
#include "token.h"
#include "lexer.h"
#include "binoperator.h"
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
		BinOp* expr();	
		BinOp* factor();
		BinOp* term();
		BinOp* parser();
		void showTree(BinOp* node);
};

#endif
