#ifndef BINOPERATOR_H_
#define BINOPERATRO_H_
#include "token.h"
class BinOp 
{
	public:
			Token token;
			BinOp* left;
			BinOp* right;
	public:
			BinOp(BinOp* node);
			BinOp(BinOp* left, Token _operator, BinOp* right);
			~BinOp();

};

#endif
