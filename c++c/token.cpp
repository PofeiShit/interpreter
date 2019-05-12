#include "token.h"

using namespace std;

const unordered_map<string, int> Token::_kwTypeMap = {
	{ "auto", Token::AUTO},

	{ "_Thread_local", Token::THREAD_LOCAL},
};

const unordered_map<int, const char*> Token::_TagLexemeMap = {
	{ '(', "(" },
	{ ')', ")" },
	{ '[', "[" },
	{ ']', "]" },
	{ ':', ":" },
	{ ',', "," },
	{ ';', ";" },
	{ '+', "+" },
	{ '-', "-" },
	{ '*', "*" },
	{ '/', "/" },
	{ '|', "|" },
	{ '&', "&" },
	{ '<', "<" },
	{ '>', ">" },
	{ '=', "=" },
	{ '.', "." },
	{ '%', "%" },
	{ '{', "{" },
	{ '}', "}" },
	{ '^', "^" },
	{ '~', "~" },
	{ '!', "!" },
	{ '?', "?" },
	{ '#', "#" },
    
	{ Token::DSHARP, "##" },
	{ Token::PTR_OP, "->" },
	{ Token::INC_OP, "++" },
	{ Token::DEC_OP, "--" },
	{ Token::LEFT_OP, "<<" },
	{ Token::RIGHT_OP, ">>" },
	{ Token::LE_OP, "<=" },
	{ Token::GE_OP, ">=" },
	{ Token::EQ_OP, "==" },
	{ Token::NE_OP, "!=" },
	{ Token::AND_OP, "&&" },
	{ Token::OR_OP, "||" },
	{ Token::MUL_ASSIGN, "*=" },
	{ Token::DIV_ASSIGN, "/=" },
	{ Token::MOD_ASSIGN, "%=" },
	{ Token::ADD_ASSIGN, "+=" },
	{ Token::SUB_ASSIGN, "-=" },
	{ Token::LEFT_ASSIGN, "<<=" },
	{ Token::RIGHT_ASSIGN, ">>=" },
	{ Token::AND_ASSIGN, "&=" },
	{ Token::XOR_ASSIGN, "^=" },
	{ Token::OR_ASSIGN, "|=" },
	{ Token::ELLIPSIS, "..."},

	/* key words */
	{ Token::AUTO, "auto"},
		
	{ Token::THREAD_LOCAL, "_Thread_local"},
};
