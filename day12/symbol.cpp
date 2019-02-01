#include "symbol.h"

void SymbolTableBuilder::visit(Program* node)
{
	visit(static_cast<Block*>(node->left));
}
void SymbolTableBuilder::visit(Block* node)
{

	for(int i = 0; i < node->declarations.size(); i++){
		for(int j  = 0; j < node->declarations[i].size(); j++){
			visit(static_cast<VarDecl*>(node->declarations[i][j]));
		}
	}
	visit(static_cast<Compound*>(node->left));
}
void SymbolTableBuilder::visit(VarDecl* node)
{
	AST* type_node = node->right;	
	std::string type_name = type_node->token.value;	
	Symbol* symbol_type = symbol_table.lookUp(type_name); 
	AST* var_node = node->left;
	std::string var_name = var_node->token.value;
	VarSymbol* var_symbol = new VarSymbol(var_name, type_name);
	symbol_table.define(static_cast<Symbol*>(var_symbol));
}
void SymbolTableBuilder::visit(Compound* node)
{
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
void SymbolTableBuilder::visit(NoOperator* node)
{
	return ;
}
void SymbolTableBuilder::visit(ProcedureDecl *node)
{
	return ;
}
void SymbolTableBuilder::visit(BinOp *node)
{
	AST* left = node->left;
	AST* right = node->right;
	NodeType type = left->getType();
	if(type == BINOP)
		visit(static_cast<BinOp*>(left));
	else if(type == NUM)
		visit(static_cast<Num*>(left));
	else if(type == UNARY)
		visit(static_cast<UnaryOperator*>(left));
	else if(type == VARIABLE)
		visit(static_cast<Variable*>(left));

	type = right->getType();
	if(type == BINOP)
		visit(static_cast<BinOp*>(right));
	else if(type == NUM)
		visit(static_cast<Num*>(right));
	else if(type == UNARY)
		visit(static_cast<UnaryOperator*>(right));
	else if(type == VARIABLE)
		visit(static_cast<Variable*>(right));
}
void SymbolTableBuilder::visit(Num* node)
{
	return ;
}
void SymbolTableBuilder::visit(UnaryOperator* node)
{
	AST* father = (AST*)node;
	AST* son = father->left;
	NodeType type = son->getType();
	if(type == BINOP)
		visit(static_cast<BinOp*>(son));
	else if(type == NUM)
		visit(static_cast<Num*>(son));
	else if(type == UNARY)
		visit(static_cast<UnaryOperator*>(son));
	else if(type == VARIABLE)
		visit(static_cast<Variable*>(son));

}
void SymbolTableBuilder::visit(Type *node)
{
	return ;
}
void SymbolTableBuilder::visit(Assign* node)
{
	AST* var_node = node->left;	
	std::string var_name = var_node->token.value;
	Symbol* var_symbol = symbol_table.lookUp(var_name);
	if(var_symbol == NULL){
		fprintf(stderr, "错误的标识符:%s", var_name.c_str());
	}

	NodeType type = node->right->getType();
	if(type == BINOP)
		visit(static_cast<BinOp*>(node->right));
	else if(type == NUM)
		visit(static_cast<Num*>(node->right));
	else if(type == UNARY)
		visit(static_cast<UnaryOperator*>(node->right));
}
void SymbolTableBuilder::visit(Variable *node)
{
	std::string var_name = node->var_name;	
	Symbol* var_symbol = symbol_table.lookUp(var_name);
	if(var_symbol == NULL){
		fprintf(stderr, "错误的标识符:%s", var_name.c_str());
	}
}
