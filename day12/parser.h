#ifndef PARSER_H_
#define PARSER_H_
#include "token.h"
#include "lexer.h"
#include "ast.h"

extern std::map<std::string, std::string> VAR_TYPES;
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
		AST* variable();
		AST* empty();
		AST* assignment_statement();
		AST* statement();
		std::vector<AST*> statement_list();
		AST* compound_statement();
		AST* program();
		AST* block();
		std::vector<std::vector<AST*> > declarations();
		std::vector<AST*> variable_declaration();
		AST* type_spec();
		void showTree(AST* node);
};

#endif
