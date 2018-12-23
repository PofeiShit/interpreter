#include "interpreter.h"
Interpreter::Interpreter(const Lexer _lexer)
{
	lexer = _lexer;
	current_token = lexer.get_next_token();
}
void Interpreter::eat(const std::string &token_type)
{
	if(current_token.type == token_type)
		current_token = lexer.get_next_token();
	else
		error();
}
void Interpreter::error()
{
	fprintf(stderr, "Invalid syntax\n");
}
int Interpreter::factor()
{
	Token token = current_token;
	if(token.type == INTEGER){
			eat(INTEGER);
			return atoi(token.value.c_str());
	}
	else if(current_token.type == LPAREN){
		eat(LPAREN);
		long long int res = expr();
		if(current_token.type == RPAREN)
			eat(RPAREN);
		return res;
	}
}
int Interpreter::term()
{
	long long int result = factor();
	while(current_token.type == MUL || current_token.type == DIV){
		Token token = current_token;
		if(token.type == MUL){
			eat(MUL);
			result *= factor();
		}else if(token.type == DIV){
			eat(DIV);
			result /= factor();
		}
	}
	return result; 
}
int Interpreter::expr()
{
	// set current token to the first token taken from the input

	long long int result = term();
	while(current_token.type == PLUS || current_token.type == MINUS){
		Token token = current_token;
		if(token.type == PLUS){
			eat(PLUS);
			result += term();
		}else if(token.type == MINUS){
			eat(MINUS);
			result -= term();
		}
	}
	return result;

}
