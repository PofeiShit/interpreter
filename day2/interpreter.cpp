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
						return Token(SUB, "-");
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
int Interpreter::expr()
{
		// set current token to the first token taken from the input
		current_token = get_next_token();
		// we expect the current token to be a single-digit integer
		Token left = current_token;
		eat(INTEGER);

		// we expect the current token to be a '+' token
		Token op = current_token;
		if(op.type == PLUS)
				eat(PLUS);
		else if(op.type == SUB)
				eat(SUB);

		// we expect the current token to be a single-digit integer
		Token right = current_token;
		eat(INTEGER);
		// after the above call the self.current_token is set to EOF token at this point INTEGER PLUS INTEGER sequence of tokens has been successfully found and the method can just return the result of adding two integers, thus effectively interpreter client input
		int result;
		if(op.type == PLUS)
				result = atoi(left.value.c_str()) + atoi(right.value.c_str());
		else if(op.type == SUB)
				result = atoi(left.value.c_str()) - atoi(right.value.c_str());
		return result;
}
