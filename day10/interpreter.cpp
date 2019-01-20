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
		NodeType type = left->getType();
		if(type == BINOP)
				l = visit(static_cast<BinOp*>(left));
		else if(type == NUM)
				l = visit(static_cast<Num*>(left));
		else if(type == UNARY)
				l = visit(static_cast<UnaryOperator*>(left));
		else if(type == VARIABLE)
				l = visit(static_cast<Variable*>(left));

		type = right->getType();
		if(type == BINOP)
				r = visit(static_cast<BinOp*>(right));
		else if(type == NUM)
				r = visit(static_cast<Num*>(right));
		else if(type == UNARY)
				r = visit(static_cast<UnaryOperator*>(right));
		else if(type == VARIABLE)
				r = visit(static_cast<Variable*>(right));

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
int Interpreter::visit(UnaryOperator *node)
{
		int value = 0;
		AST* father = (AST*)node;
		AST* son = father->left;
		NodeType type = son->getType();
		if(type == BINOP)
				value = visit(static_cast<BinOp*>(son));
		else if(type == NUM)
				value = visit(static_cast<Num*>(son));
		else if(type == UNARY)
				value = visit(static_cast<UnaryOperator*>(son));
		else if(type == VARIABLE)
				value = visit(static_cast<Variable*>(son));

		if(father->token.type == PLUS)
				return value;
		else if(father->token.type == MINUS)
				return -value;
}
void Interpreter::visit(Compound *node)
{
		int value = 0;
		for(int i = 0; i < node->children.size(); i++){
			NodeType type = node->children[i]->getType(); 
			if(type == COMPOUND)
				visit(static_cast<Compound*>(node->children[i]));	
			else if(type == ASSIGNNODE)
				visit(static_cast<Assign*>(node->children[i]));
			else if(type == NOOPERATOR)
				visit(static_cast<NoOperator*>(node->children[i]));
		}
}
void Interpreter::visit(Assign *node)
{
	Variable *n = static_cast<Variable*>(node->left);
	std::string var_name = n->var_name;	
	NodeType type = node->right->getType();
	int value;
	if(type == BINOP)
		value = visit(static_cast<BinOp*>(node->right));
	else if(type == NUM)
		value = visit(static_cast<Num*>(node->right));
	else if(type == UNARY)
		value = visit(static_cast<UnaryOperator*>(node->right));

	GLOBAL_SCOPE[var_name] = value;
}
int Interpreter::visit(Variable *node)
{
	std::string var_name = node->var_name;
	if(GLOBAL_SCOPE.find(var_name) != GLOBAL_SCOPE.end())
			return GLOBAL_SCOPE[var_name];
	error();
	return -1;
}
void Interpreter::visit(NoOperator *node)
{
	return;
}
void Interpreter::error()
{
	fprintf(stderr, "invalid node\n");
}
int Interpreter::interpret()
{
		AST* tree = parser.parser();
		NodeType type = tree->getType();
		if(type == BINOP) 
				return visit(static_cast<BinOp*>(tree)); 
		else if(type == NUM)
				return visit(static_cast<Num*>(tree)); 
		else if(type == UNARY)
				return visit(static_cast<UnaryOperator*>(tree));
		else if(type == COMPOUND)
				visit(static_cast<Compound*>(tree));
		else if(type == ASSIGNNODE)
				visit(static_cast<Assign*>(tree));
		else if(type == NOOPERATOR)
				visit(static_cast<NoOperator*>(tree));
		else if(type == VARIABLE){
				error();
				return -1;
		}

}
