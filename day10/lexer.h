#ifndef LEXER_H_
#define LEXER_H_
#include "token.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>
typedef std::map<std::string, Token> strTokenType;
class Lexer
{
		public:
				std::string text;
				size_t pos;
				char current_char;
				static strTokenType RESERVED_KEYWORDS;
		public:
				Lexer(){}
				Lexer(const std::string &_text):text(_text), pos(0){
						current_char = text[pos];
				}
				void error();
				Token get_next_token();
				void skip_whitespace();
				void skip_comment();
				void advance();
				char peek();
				Token get_id();
				Token number();
				
};
#endif
