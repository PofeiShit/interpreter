#include "interpreter.h"

Interpreter::Interpreter(){
}
Interpreter::Interpreter(const Parser& parser):parser(parser), tree(NULL)
{
}
Interpreter::Interpreter(AST* _tree):tree(_tree){}
Interpreter::~Interpreter()
{
}
template<typename T>
T Interpreter::visit(BinOp *node)
{
	AST* left = node->left;
	AST* right = node->right;
	T l, r;
	NodeType type = left->getType();
	if(type == BINOP)
		l = visit<T>(static_cast<BinOp*>(left));
	else if(type == NUM)
		l = visit<T>(static_cast<Num*>(left));
	else if(type == UNARY)
		l = visit<T>(static_cast<UnaryOperator*>(left));
	else if(type == VARIABLE)
		l = visit<T>(static_cast<Variable*>(left));

	type = right->getType();
	if(type == BINOP)
		r = visit<T>(static_cast<BinOp*>(right));
	else if(type == NUM)
		r = visit<T>(static_cast<Num*>(right));
	else if(type == UNARY)
		r = visit<T>(static_cast<UnaryOperator*>(right));
	else if(type == VARIABLE)
		r = visit<T>(static_cast<Variable*>(right));

	if(node->token.type	== PLUS)
		return l + r;
	if(node->token.type	== MINUS)
		return l - r;
	if(node->token.type	== MUL)
		return l * r;
	if(node->token.type	== INTEGER_DIV)
		return l / r;
	if(node->token.type == FLOAT_DIV)
		return (float)l / (float)r;
}
template<typename T>
T Interpreter::visit(Num *node)
{
	if(node->token.type == INTEGER_CONST)
		return node->get_ValueI();
	else if(node->token.type == REAL_CONST)
		return node->get_ValueF();
}
	template<typename T>
T Interpreter::visit(UnaryOperator *node)
{
	T value;
	AST* father = (AST*)node;
	AST* son = father->left;
	NodeType type = son->getType();
	if(type == BINOP)
		value = visit<T>(static_cast<BinOp*>(son));
	else if(type == NUM)
		value = visit<T>(static_cast<Num*>(son));
	else if(type == UNARY)
		value = visit<T>(static_cast<UnaryOperator*>(son));
	else if(type == VARIABLE)
		value = visit<T>(static_cast<Variable*>(son));

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
	if(VAR_TYPES[n->var_name] == INTEGER){	
		int value;
		if(type == BINOP)
			value = visit<int>(static_cast<BinOp*>(node->right));
		else if(type == NUM)
			value = visit<int>(static_cast<Num*>(node->right));
		else if(type == UNARY)
			value = visit<int>(static_cast<UnaryOperator*>(node->right));
		GLOBAL_SCOPE[var_name] = std::to_string(value);
	}
	else if(VAR_TYPES[n->var_name] == REAL){	
		float value;
		if(type == BINOP)
			value = visit<float>(static_cast<BinOp*>(node->right));
		else if(type == NUM)
			value = visit<float>(static_cast<Num*>(node->right));
		else if(type == UNARY)
			value = visit<float>(static_cast<UnaryOperator*>(node->right));
		GLOBAL_SCOPE[var_name] = std::to_string(value);
	}
}
	template<typename T>
T Interpreter::visit(Variable *node)
{
	std::string var_name = node->var_name;
	if(GLOBAL_SCOPE.find(var_name) != GLOBAL_SCOPE.end()){
		if(VAR_TYPES[node->var_name] == INTEGER)
			return atoi(GLOBAL_SCOPE[var_name].c_str());
		else if(VAR_TYPES[node->var_name] == REAL)
			return atof(GLOBAL_SCOPE[var_name].c_str());
	}
	error();
	return -1;
}
void Interpreter::visit(NoOperator *node)
{
	return;
}
void Interpreter::visit(ProcedureDecl *node)
{
	return;		
}
void Interpreter::visit(Program *node)
{
	return visit(static_cast<Block*>(node->left));
}
void Interpreter::visit(Block *node)
{
	for(int i = 0; i < node->declarations.size(); i++){
		for(int j  = 0; j < node->declarations[i].size(); j++){
			visit(static_cast<VarDecl*>(node->declarations[i][j]));
		}
	}
	visit(static_cast<Compound*>(node->left));
}
void Interpreter::visit(VarDecl *node)
{
	return ;
}
void Interpreter::visit(Type *node)
{
	return ;
}
void Interpreter::error()
{
	fprintf(stderr, "invalid node\n");
}
void Interpreter::interpret()
{
	if(tree == NULL){
		error();
		return;
	}
	visit(static_cast<Program*>(tree));
}
