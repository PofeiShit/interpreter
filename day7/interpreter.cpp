#include "interpreter.h"

Interpreter::Interpreter(){
}
Interpreter::Interpreter(const Parser& parser):parser(parser)
{
}
Interpreter::~Interpreter()
{
}
int Interpreter::visit(BinOp *node)
{
		AST* left = node->left;
		AST* right = node->right;
		int l = 0, r = 0;
		if(left->getType() == BINOP)
				l = visit(static_cast<BinOp*>(left));
		else if(left->getType() == NUM)
				l = visit(static_cast<Num*>(left));

		if(right->getType() == BINOP)
				r = visit(static_cast<BinOp*>(right));
		else if(right->getType() == NUM)
				r = visit(static_cast<Num*>(right));
		if(node->token.type	== PLUS)
				return l + r;
		if(node->token.type	== MINUS)
				return l - r;
		if(node->token.type	== MUL)
				return l * r;
		if(node->token.type	== DIV)
				return l / r;
}
int Interpreter::visit(Num *node)
{
		return node->getValue();
}
int Interpreter::interpret()
{
		AST* tree = parser.parser();
		if(tree->getType() == BINOP) 
				return visit(static_cast<BinOp*>(tree)); 
		else if(tree->getType() == NUM)
				return visit(static_cast<Num*>(tree)); 
}
