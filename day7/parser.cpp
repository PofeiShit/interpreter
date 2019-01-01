#include "parser.h"
Parser::Parser()
{
}
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
BinOp* Parser::factor()
{
	Token token = current_token;
	if(token.type == INTEGER){
			eat(INTEGER);
			return new BinOp(NULL, token, NULL); // number  
	}
	else if(token.type == LPAREN){
		eat(LPAREN);
		BinOp* ast = expr();
		eat(RPAREN);
		return ast;
	}
}
BinOp* Parser::term()
{
	BinOp* node = factor();
	while(current_token.type == MUL || current_token.type == DIV){
		Token token = current_token;
		if(token.type == MUL){
			eat(MUL);
		}else if(token.type == DIV){
			eat(DIV);
		}
		BinOp* newNode = new BinOp(node, token, factor());
		node = newNode;
	}
	return node; 
}
BinOp* Parser::expr()
{
	// set current token to the first token taken from the input

	BinOp* ast = term();
	BinOp* node = new BinOp(ast); 
	while(current_token.type == PLUS || current_token.type == MINUS){
		Token token = current_token;
		if(token.type == PLUS){
			eat(PLUS);
		}else if(token.type == MINUS){
			eat(MINUS);
		}
		BinOp* newNode = new BinOp(node, token, term());
		node = newNode;
	}
	return node;
}
void Parser::showTree(BinOp* node)
{
	if(node != NULL){
		node->token.show();
		showTree(node->left);
		showTree(node->right);
	}	
}
BinOp* Parser::parser()
{
	BinOp* node = expr();
//	showTree(node);
	return node;
}
