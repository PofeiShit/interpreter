#include "interpreter.h"

Token Interpreter::get_next_token()
{
	std::string text(text);

	// is self.pos index  past the end of the self.text ? if so, then return EOF token because there is no more input left to convert into tokens
	if(pos > text.length() - 1)
		return Token(EOF_, None);

	// get a character at the position self.pos and decide what token to create based on the single character
	char current_char = text[pos];
	// if the character is a digit then convert it to integer, create an INTEGER token, increment self.pos index to point to the next character after the digit, and return the INTEGER token
	if(isdigit(current_char)){
		Token token = Token(INTEGER, current_char - '0');
		pos++;
		return token;
	}
	if(current_char == '+'){
		Token token = Token(PLUS, current_char);
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
	eat(PLUS);
   
	// we expect the current token to be a single-digit integer
	Token right = current_token;
	eat(INTEGER);

	// after the above call the self.current_token is set to EOF token at this point INTEGER PLUS INTEGER sequence of tokens has been successfully found and the method can just return the result of adding two integers, thus effectively interpreter client input
	int result = left.value - '0' + right.value - '0';
	return result;
}
