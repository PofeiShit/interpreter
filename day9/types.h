#ifndef TYPES_H_
#define TYPES_H_

#include <string>
#include <iostream>
#include <stdlib.h>

enum NodeType
{
	BINOP, NUM, UNARY, COMPOUND, ASSIGNNODE, VARIABLE, NOOPERATOR
};
/* 	终结符常量 */
const std::string INTEGER = "INTEGER";
const std::string PLUS = "PLUS";
const std::string EOF_ = "EOF";
const std::string MINUS = "MINUS";
const std::string MUL = "MUL";
const std::string DIV = "DIV";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string ASSIGN = "ASSIGN";
const std::string SEMI = "SEMI";
const std::string DOT = "DOT";
const std::string BEGIN = "BEGIN";
const std::string END = "END";
const std::string ID = "ID";

const char None = '\0';
#endif
