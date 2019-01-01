#include "binoperator.h"

BinOp::BinOp(AST* node){
		token = ((BinOp*)node)->token;
		left = ((BinOp*)node)->left;
		right = ((BinOp*)node)->right;
}
BinOp::BinOp(AST* left, Token _operator, AST* right):token(_operator), left(left), right(right)
{

}
BinOp::~BinOp()
{

}
