#include "parser.h"
Parser::Parser(const Lexer _lexer)
{
	lexer = _lexer;
	current_token = lexer.get_next_token();
}
void Parser::eat(const std::string &token_type)
{
	if(current_token.type == token_type)
		current_token = lexer.get_next_token();
	else
		error();
}
void Parser::error()
{
	fprintf(stderr, "Warning Invalid input\n");
}
AST* Parser::factor()
{
	Token token = current_token;
	if(token.type == INTEGER){
			eat(INTEGER);
			AST* ast = new Num(token);
			return ast;
	}
	else if(token.type == LPAREN){
		eat(LPAREN);
		AST* ast = new BinOp(expr());
		eat(RPAREN);
		return ast;
	}
}
AST* Parser::term()
{
	AST* ast = new BinOp(factor());
	AST* node;
	while(current_token.type == MUL || current_token.type == DIV){
		Token token = current_token;
		if(token.type == MUL){
			eat(MUL);
		}else if(token.type == DIV){
			eat(DIV);
		}
		AST* right = new BinOp(factor());
		node = new BinOp(ast, token, right);
	}
	return node; 
}
AST* Parser::expr()
{
	// set current token to the first token taken from the input

	AST* ast = new BinOp(term());
	AST* node;
	while(current_token.type == PLUS || current_token.type == MINUS){
		Token token = current_token;
		if(token.type == PLUS){
			eat(PLUS);
		}else if(token.type == MINUS){
			eat(MINUS);
		}
		AST* right = new BinOp(factor());
		node = new BinOp(ast, token, right);
	}
	return node;
}
AST* Parser::parser()
{
	AST* node = expr();
	std::cout << node << std::endl;
	return node;
}
