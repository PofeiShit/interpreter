#include "semantic.h"

void SemanticAnalyzer::visit(Program* node)
{
	visit(static_cast<Block*>(node->left));
}
void SemanticAnalyzer::visit(Block* node)
{

	for(int i = 0; i < node->declarations.size(); i++){
		for(int j  = 0; j < node->declarations[i].size(); j++){
			visit(static_cast<VarDecl*>(node->declarations[i][j]));
		}
	}
	visit(static_cast<Compound*>(node->left));
}
void SemanticAnalyzer::visit(VarDecl* node)
{
	AST* type_node = node->right;	
	std::string type_name = type_node->token.value;	
	Symbol* symbol_type = symbol_table.lookUp(type_name); 

	AST* var_node = node->left;
	std::string var_name = var_node->token.value;
	if(symbol_table._symbols.find(var_name) != symbol_table._symbols.end()){
		fprintf(stderr, "错误:发现重复的标识符:%s\n", var_name.c_str());
		return ;
	}
	VarSymbol* var_symbol = new VarSymbol(var_name, type_name);
	symbol_table.insert(static_cast<Symbol*>(var_symbol));
}
void SemanticAnalyzer::visit(Compound* node)
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
void SemanticAnalyzer::visit(NoOperator* node)
{
	return ;
}
void SemanticAnalyzer::visit(ProcedureDecl *node)
{
	return ;
}
void SemanticAnalyzer::visit(BinOp *node)
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
void SemanticAnalyzer::visit(Num* node)
{
	return ;
}
void SemanticAnalyzer::visit(UnaryOperator* node)
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
void SemanticAnalyzer::visit(Type *node)
{
	return ;
}
void SemanticAnalyzer::visit(Assign* node)
{

	NodeType type = node->right->getType();
	if(type == BINOP)
		visit(static_cast<BinOp*>(node->right));
	else if(type == NUM)
		visit(static_cast<Num*>(node->right));
	else if(type == UNARY)
		visit(static_cast<UnaryOperator*>(node->right));
	else if(type == VARIABLE)
		visit(static_cast<Variable*>(node->right));

	AST* var_node = node->left;	
	std::string var_name = var_node->token.value;
	Symbol* var_symbol = symbol_table.lookUp(var_name);
	if(var_symbol == NULL){
		fprintf(stderr, "引用了不存在的标识符:%s\n", var_name.c_str());
	}
}
void SemanticAnalyzer::visit(Variable *node)
{
	std::string var_name = node->var_name;	
	Symbol* var_symbol = symbol_table.lookUp(var_name);
	if(var_symbol == NULL){
		fprintf(stderr, "引用了不存在的标识符:%s\n", var_name.c_str());
	}
}
