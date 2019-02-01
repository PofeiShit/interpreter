#include "lexer.h"

std::pair<std::string, Token> pairArray[] =
{
	std::make_pair("PROGRAM", Token(PROGRAM, "PROGRAM")),
	std::make_pair("VAR", Token(VAR, "VAR")),
	std::make_pair("DIV", Token(INTEGER_DIV, "DIV")),
	std::make_pair("INTEGER", Token(INTEGER, "INTEGER")),
	std::make_pair("REAL", Token(REAL, "REAL")),
	std::make_pair("BEGIN", Token(BEGIN, "BEGIN")),
	std::make_pair("END", Token(END, "END")),
	std::make_pair("PROCEDURE", Token(PROCEDURE, "PROCEDURE"))
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
	while(current_char != None && (isalnum(current_char) || current_char == '_')){
		if(isalnum(current_char)){
			result += toupper(current_char);
		} else if(current_char == '_'){
			result += current_char;
		}
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
void Lexer::skip_comment()
{
	while(current_char != '}')
			advance();
	advance();
}
Token Lexer::number()
{
	std::string result("");
	while(current_char != None && isdigit(current_char)){
		result += current_char;	
		advance();
		if(current_char == '.'){
			result += current_char;
			advance();
			while(current_char != None && isdigit(current_char)){
				result += current_char;
				advance();
			}
			return Token(REAL_CONST, result);
		}
	}
	return Token(INTEGER_CONST, result);
}
Token Lexer::get_next_token()
{
	while(current_char != None){
		if(current_char == '{'){
			advance();
			skip_comment();
			continue;
		}
		if(current_char == ' ' || current_char == '\t'){
			skip_whitespace();
			continue;
		}	
		if(isdigit(current_char)){
			return number();
		}
		if(current_char == ','){
			advance();
			return Token(COMMA, ",");
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
			return Token(FLOAT_DIV, "/");		
		}
		if(current_char == '('){
			advance();
			return Token(LPAREN, "(");
		}
		if(current_char == ')'){
			advance();
			return Token(RPAREN, ")");
		}
		if(isalpha(current_char) || current_char == '_')
			return get_id();
		if(current_char == ':' && peek() == '='){
			advance();
			advance();
			return Token(ASSIGN, ":=");
		}
		if(current_char == ':'){
			advance();
			return Token(COLON, ":");
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
