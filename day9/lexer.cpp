#include "lexer.h"

std::pair<std::string, Token> pairArray[] =
{
		std::make_pair("BEGIN", Token(BEGIN, "BEGIN")),
		std::make_pair("END", Token(END, "END"))
};
strTokenType Lexer::RESERVED_KEYWORDS(pairArray, pairArray + sizeof(pairArray) / sizeof(pairArray[0]));
char Lexer::peek()
{
	size_t p = pos + 1;
	if(p >= text.length())
			return None;
	else
			return text[p];
}
Token Lexer::get_id()
{
	std::string result = "";
	while(current_char != None && isalnum(current_char)){
		result += current_char;
		advance();
	}
	if(RESERVED_KEYWORDS.find(result) != RESERVED_KEYWORDS.end())
			return RESERVED_KEYWORDS[result];
	else 
			return Token(ID, result); 
}
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
	while(current_char != None && (current_char == ' ' || current_char == '\t'))
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
		if(current_char == ' ' || current_char == '\t'){
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
		if(current_char == '('){
			advance();
			return Token(LPAREN, "(");
		}
		if(current_char == ')'){
			advance();
			return Token(RPAREN, ")");
		}
		if(isalpha(current_char))
			return get_id();
		if(current_char == ':' && peek() == '='){
			advance();
			advance();
			return Token(ASSIGN, ":=");
		}
		if(current_char == ';'){
			advance();
			return Token(SEMI, ";");
		}
		if(current_char == '.'){
			advance();
			return Token(DOT, ".");
		}
		error();
	}
	return Token(EOF_, "");
}
void Lexer::error()
{
	fprintf(stderr, "%s", "Invalid character\n");
}
