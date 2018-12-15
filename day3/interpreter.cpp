#include "interpreter.h"

void Interpreter::skip_whitespace()
{
	while(current_char != None && current_char == ' ')
		advance();
}
std::string Interpreter::integer()
{
	std::string result;
	while(current_char != None && isdigit(current_char)){
		result.push_back(current_char);
		advance();
	}
	return result;
}
Token Interpreter::get_next_token()
{
	while(current_char != None){
		if(current_char == ' '){
			skip_whitespace();
			continue;
		}	
		if(isdigit(current_char)){
			return Token(INTEGER, integer());
		}
		if(current_char == '+'){
			advance();
			return Token(PLUS, "+");
		}
		if(current_char == '-'){
			advance();
			return Token(MINUS, "-");
		}
		if(current_char == '*'){
			advance();
			return Token(MUL, "*");	
		}
		if(current_char == '/'){
			advance();
			return Token(DIV, "/");		
		}
		error();
	}
	return Token(EOF_, "");
}
void Interpreter::error()
{
	fprintf(stderr, "%s", "Error parsing input\n");
}
void Interpreter::advance()
{
	pos++;
	if(pos > text.length() - 1)
		current_char = None;
	else
		current_char = text[pos];
}
void Interpreter::eat(const std::string &token_type)
{
	if(current_token.type == token_type)
		current_token = get_next_token();
	else
		error();
}
int Interpreter::term()
{
	Token token = current_token;
	eat(INTEGER);
	return atoi(token.value.c_str());
}
int Interpreter::expr()
{
	// set current token to the first token taken from the input
	current_token = get_next_token();

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
