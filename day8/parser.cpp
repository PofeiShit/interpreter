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
AST* Parser::factor()
{
		Token token = current_token;
		if(token.type == PLUS){
			eat(PLUS);
			AST* t = factor();
			UnaryOperator* node = new UnaryOperator(t, token);
			return static_cast<AST*>(node);
		}
		else if(token.type == MINUS){
			eat(MINUS);
			AST* t = factor();
			UnaryOperator* node = new UnaryOperator(t, token);
			return static_cast<AST*>(node);
		}
		else if(token.type == INTEGER){
				eat(INTEGER);
				Num* node = new Num(token); // number  
				return static_cast<AST*>(node);
		}
		else if(token.type == LPAREN){
				eat(LPAREN);
				AST* ast = expr();
				eat(RPAREN);
				return ast;
		}else{
			std::runtime_error e("no token error");
			throw(e);
		}
}
AST* Parser::term()
{
		AST* node = factor();
		while(current_token.type == MUL || current_token.type == DIV){
				Token token = current_token;
				if(token.type == MUL){
						eat(MUL);
				}else if(token.type == DIV){
						eat(DIV);
				}
				BinOp* newNode = new BinOp(node, token, factor());
				node = static_cast<AST*>(newNode);
		}
		return node; 
}
AST* Parser::expr()
{
		// set current token to the first token taken from the input
		AST* node = term();
		while(current_token.type == PLUS || current_token.type == MINUS){
				Token token = current_token;
				if(token.type == PLUS){
						eat(PLUS);
				}else if(token.type == MINUS){
						eat(MINUS);
				}
				BinOp* newNode = new BinOp(node, token, term());
				node = static_cast<AST*>(newNode);
		}
		return node;
}
void Parser::showTree(AST* node)
{
		if(node != NULL){
				node->token.show();
				if(node->left != NULL)
					showTree(node->left);
				if(node->right != NULL)
					showTree(node->right);
		}	
}
AST* Parser::parser()
{
		AST* node = expr();
//		showTree(node);
		return node;
}
