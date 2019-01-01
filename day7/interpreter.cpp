#include "interpreter.h"

Interpreter::Interpreter(){
}
Interpreter::Interpreter(const Parser parser):parser(parser)
{
}
Interpreter::~Interpreter()
{
}
int Interpreter::visitBinOp(BinOp* node)
{
	if(node->left == NULL && node->right == NULL)
		return atoi(node->token.value.c_str());
	if(node->token.type == PLUS)
		return visitBinOp(node->left) + visitBinOp(node->right);
	else if(node->token.type == MINUS)
		return visitBinOp(node->left) - visitBinOp(node->right);
	else if(node->token.type == MUL)
		return visitBinOp(node->left) * visitBinOp(node->right);
	else if(node->token.type == DIV)
		return visitBinOp(node->left) / visitBinOp(node->right);	
}
int Interpreter::interpret()
{
	BinOp* tree = parser.parser();
	return visitBinOp(tree); 
}
