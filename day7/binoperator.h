#ifndef BINOPERATOR_H_
#define BINOPERATRO_H_
#include "ast.h"

class BinOp : public AST
{
	public:
			Token token;
			AST* left;
			AST* right;
	public:
			BinOp(AST* node);
			BinOp(AST* left, Token _operator, AST* right);
			~BinOp();

};

#endif
