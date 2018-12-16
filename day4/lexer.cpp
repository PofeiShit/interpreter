#include "lexer.h"

void Lexer::advance()
{
	pos++;
	if(pos > text.length() - 1)
		current_char = None;
	else
		current_char = text[pos];
}
void Lexer::skip_whitespace()
{
	while(current_char != None && current_char == ' ')
		advance();
}
std::string Lexer::integer()
{
	std::string result;
	while(current_char != None && isdigit(current_char)){
		result.push_back(current_char);
		advance();
	}
	return result;
}
Token Lexer::get_next_token()
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
void Lexer::error()
{
	fprintf(stderr, "%s", "Invalid character\n");
}
