#include "interpreter.h"

void Interpreter::skip_blank(char &current_char)
{
	while(current_char != None && current_char == ' '){
		pos++;
		current_char = text[pos];
	}
}
Token Interpreter::get_number(char &current_char)
{
	std::string num;
	while(current_char != None && isdigit(current_char)){
		num.push_back(current_char);
		pos++;
		current_char = text[pos];
	}
	return Token(INTEGER, num);
}
Token Interpreter::get_next_token()
{
	std::string Text(text);
	// is self.pos index  past the end of the self.text ? if so, then return EOF token because there is no more input left to convert into tokens
	if(pos > Text.length() - 1)
		return Token(EOF_, "");

	// get a character at the position self.pos and decide what token to create based on the single character
	char current_char = Text[pos];
	// if the character is a digit then convert it to integer, create an INTEGER token, increment self.pos index to point to the next character after the digit, and return the INTEGER token
	if(current_char == ' '){
		skip_blank(current_char);
	}	
	if(isdigit(current_char)){
		Token token = get_number(current_char);
		return token;
	}
	if(current_char == '+'){
		Token token = Token(PLUS, "+");
		pos++;
		return token;
	}
	if(current_char == '-'){
		Token token = Token(SUB, "-");
		pos++;
		return token;
	}
}
void Interpreter::error()
{
	fprintf(stderr, "%s", "Error parsing input\n");
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
