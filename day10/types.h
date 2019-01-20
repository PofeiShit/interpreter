#ifndef TYPES_H_
#define TYPES_H_

#include <string>
#include <iostream>
#include <stdlib.h>

enum NodeType
{
	BINOP, NUM, UNARY, COMPOUND, ASSIGNNODE, VARIABLE, NOOPERATOR, PROGRAMNODE, BLOCK, VARDECL, TYPE
};
/* 	终结符常量 */
const std::string INTEGER = "INTEGER";
const std::string REAL = "REAL";
const std::string INTEGER_CONST = "INTEGER_CONST";
const std::string REAL_CONST = "REAL_CONST";
const std::string PLUS = "PLUS";
const std::string EOF_ = "EOF";
const std::string MINUS = "MINUS";
const std::string MUL = "MUL";
const std::string INTEGER_DIV = "INTEGER_DIV";
const std::string FLOAT_DIV = "FLOAT_DIV";
const std::string LPAREN = "(";
const std::string RPAREN = ")";
const std::string ASSIGN = "ASSIGN";
const std::string SEMI = "SEMI";
const std::string DOT = "DOT";
const std::string BEGIN = "BEGIN";
const std::string END = "END";
const std::string ID = "ID";
const std::string PROGRAM = "PROGRAM";
const std::string VAR = "VAR";
const std::string COLON = "COLON";
const std::string COMMA = "COMMA";

const char None = '\0';
#endif
