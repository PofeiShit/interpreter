#ifndef TYPES_H_
#define TYPES_H_

#include <string>
#include <iostream>
#include <stdlib.h>

enum NodeType
{
	BINOP, NUM
};
#if 0
enum TokenType
{
	INTEGER,
	PLUS,
	_EOF,
	MINUS,
	MUL,
	DIV,
	LPAREN,
	RPAREN,
	NONE
};
#endif
const std::string INTEGER = "INTEGER";
const std::string PLUS = "PLUS";
const std::string EOF_ = "EOF";
const std::string MINUS = "MINUS";
const std::string MUL = "MUL";
const std::string DIV = "DIV";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const char None = '\0';
#endif
