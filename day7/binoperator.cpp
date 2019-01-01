#include "binoperator.h"

BinOp::BinOp(BinOp* node){
		token = node->token;
		left = node->left;
		right = node->right;
}
BinOp::BinOp(BinOp* left, Token _operator, BinOp* right):token(_operator), left(left), right(right)
{

}
BinOp::~BinOp()
{

}
