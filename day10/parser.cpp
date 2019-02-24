#include "parser.h"
std::map<std::string, std::string> VAR_TYPES;
Parser::Parser()
{
}
Parser::Parser(const Lexer _lexer)
{
		lexer = _lexer;
		current_token = lexer.get_next_token();
}
void Parser::eat(const std::string &token_type)
{
		if(current_token.type == token_type)
				current_token = lexer.get_next_token();
		else
				error();
}
void Parser::error()
{
		fprintf(stderr, "Warning Invalid input\n");
}
AST* Parser::block()
{
		std::vector<std::vector<AST*> > declares = declarations();
		AST* compound_statements = compound_statement();
		Block* node = new Block(compound_statements);
		node->declarations = declares;
		return static_cast<AST*>(node);
}
std::vector<std::vector<AST*> > Parser::declarations()
{
	std::vector<std::vector<AST*> > declarations;
	if(current_token.type == VAR){
		eat(VAR);
		while(current_token.type == ID){
			declarations.push_back(variable_declaration());
			eat(SEMI);
		}
	}
	return declarations;
}
std::vector<AST*> Parser::variable_declaration()
{
	std::vector<AST*> var_nodes;
	var_nodes.push_back(static_cast<AST*>(new Variable(current_token)));
	eat(ID);
	while(current_token.type == COMMA){
		eat(COMMA);
		var_nodes.push_back(static_cast<AST*>(new Variable(current_token)));		
		eat(ID);
	}
	eat(COLON);
	AST* type_node = type_spec();
	std::vector<AST*> var_declarations;
	for(int i = 0; i < var_nodes.size(); i++){
		Variable* t = static_cast<Variable*>(var_nodes[i]);
		VAR_TYPES[t->token.value] = type_node->token.type;
		var_declarations.push_back(static_cast<AST*>(new VarDecl(var_nodes[i], type_node)));
	}
	return var_declarations;
}
AST* Parser::type_spec()
{
	Token token = current_token;
	if(token.type == INTEGER)
		eat(INTEGER);
	else
		eat(REAL);
	Type* node = new Type(token);
	return node;
}
AST* Parser::variable()
{
	Variable* node = new Variable(current_token);
	eat(ID);
	return static_cast<AST*>(node);
}
AST* Parser::empty()
{
	return static_cast<AST*>(new NoOperator());
}
AST* Parser::assignment_statement()
{
	AST* left = variable();
	Token token = current_token;
	eat(ASSIGN);
	AST* right = expr();
	AST* node = new Assign(left, token, right);
	return node;
}
AST* Parser::compound_statement()
{
	eat(BEGIN);
	std::vector<AST*> nodes = statement_list();
	eat(END);

	Compound *root = new Compound();
	root->children = nodes;
	return static_cast<AST*>(root);
}
AST* Parser::statement()
{
	AST* node;
	if(current_token.type == BEGIN)
		node = compound_statement();
	else if(current_token.type == ID)
		node = assignment_statement();
	else
		node = empty();
	return node;
}
std::vector<AST*> Parser::statement_list()
{
	AST* node = statement();
	std::vector<AST*> nodes;
	nodes.push_back(node);
	while(current_token.type == SEMI){
		eat(SEMI);
		nodes.push_back(statement());	
	}
	if(current_token.type == ID)
		error();
	return nodes;	
}
AST* Parser::program()
{
	eat(PROGRAM);
	AST* var_node = variable();
	std::string program_name = static_cast<Variable*>(var_node)->var_name;
	eat(SEMI);
	AST* block_node = block();
	Program* node = new Program(program_name, block_node);
	eat(DOT);
	return static_cast<AST*>(node);
}
AST* Parser::factor()
{
		Token token = current_token;
		if(token.type == PLUS){
			eat(PLUS);
			AST* t = factor();
			UnaryOperator* node = new UnaryOperator(t, token);
			return static_cast<AST*>(node);
		}
		else if(token.type == MINUS){
			eat(MINUS);
			AST* t = factor();
			UnaryOperator* node = new UnaryOperator(t, token);
			return static_cast<AST*>(node);
		}
		else if(token.type == INTEGER_CONST){
				eat(INTEGER_CONST);
				Num* node = new Num(token); // number  
				return static_cast<AST*>(node);
		}
		else if(token.type == REAL_CONST){
				eat(REAL_CONST);
				Num* node = new Num(token);
				return static_cast<AST*>(node);
		}
		else if(token.type == LPAREN){
				eat(LPAREN);
				AST* ast = expr();
				eat(RPAREN);
				return ast;
		}
		else {
				AST* node = variable();
				return node;
		}
}
AST* Parser::term()
{
		AST* node = factor();
		while(current_token.type == MUL || current_token.type == INTEGER_DIV || current_token.type == FLOAT_DIV){ Token token = current_token;
				if(token.type == MUL){
						eat(MUL);
				}else if(token.type == INTEGER_DIV){
						eat(INTEGER_DIV);
				}else if(token.type == FLOAT_DIV)
						eat(FLOAT_DIV);

				BinOp* newNode = new BinOp(node, token, factor());
				node = static_cast<AST*>(newNode);
		}
		return node; 
}
AST* Parser::expr()
{
		// set current token to the first token taken from the input
		AST* node = term();
		while(current_token.type == PLUS || current_token.type == MINUS){
				Token token = current_token;
				if(token.type == PLUS){
						eat(PLUS);
				}else if(token.type == MINUS){
						eat(MINUS);
				}
				BinOp* newNode = new BinOp(node, token, term());
				node = static_cast<AST*>(newNode);
		}
		return node;
}
void Parser::showTree(AST* node)
{
		if(node != NULL){
				node->token.show();
				if(node->getType() == COMPOUND){
					Compound* node_c = static_cast<Compound*>(node);
					for(int i = 0; i < node_c->children.size(); i++){
						showTree(node_c->children[i]);
					}
				}
				else if(node->getType() == BLOCK){
					Block* node_b = static_cast<Block*>(node);
					for(int i = 0; i < node_b->declarations.size(); i++){
						for(int j = 0; j < node_b->declarations[i].size(); j++){
							showTree(node_b->declarations[i][j]);
						}
					}
				}
				if(node->left != NULL)
					showTree(node->left);
				if(node->right != NULL)
					showTree(node->right);
		}	
}
AST* Parser::parser()
{

		AST* node = program();
		if(current_token.type != EOF_)
				error();
		//showTree(node);
		return node;
}
