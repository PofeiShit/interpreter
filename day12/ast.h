#ifndef AST_H_
#define AST_H_
#include "token.h"
#include <vector>
class AST
{
		public:
				AST(){}
				virtual	~AST(){};
		public:
				AST* left;
				AST* right;
				Token token;
				virtual NodeType getType() = 0;
};
class Num : public AST
{ 
		public:
				Num(){}
				Num(Token token){
					this->token = token;
					this->left = this->right = NULL;
				
				}
				
				NodeType getType(){
					return NUM;
				}
				~Num(){}
				int get_ValueI(){
					return atoi(token.value.c_str());
				}
				float get_ValueF(){
					return atof(token.value.c_str());
				}
};
class BinOp : public AST
{
		public:
				BinOp(){}
				BinOp(AST* left, Token _operator, AST* right)
				{
					this->token = _operator;
					this->left = left;
					this->right = right;
				}
				~BinOp(){}
				NodeType getType(){
					return BINOP;
				}

};
class UnaryOperator : public AST
{
		public:
				UnaryOperator(){}
				UnaryOperator(AST* node, Token _operator)
				{
					this->token = _operator;
					this->left = node;
					this->right = NULL;
				}
				~UnaryOperator(){}
				NodeType getType(){
					return UNARY;
				}
};
class Compound : public AST
{
	public:
		std::vector<AST*> children;
		Compound()
		{
			this->token = Token(EOF_, "COMPOUND");
			this->left = NULL;
			this->right = NULL;
		}
		NodeType getType(){
			return COMPOUND;
		}
};
class Assign : public AST
{
	public:
			Assign(){}
			Assign(AST* left, Token _operator, AST* right)
			{
				this->token = _operator;
				this->left = left;
				this->right = right;
			}
			~Assign(){}
			NodeType getType(){
				return ASSIGNNODE;	
			}
};
class Variable : public AST
{
	public:
			Variable(){}
			Variable(Token _operator)
			{
				this->token = _operator;
				this->left = NULL;
				this->right = NULL;
				var_name = _operator.value;
			}
			~Variable(){}
			NodeType getType(){
				return VARIABLE;
			}
			std::string var_name;
};
class NoOperator : public AST
{
	public:
			NoOperator()
			{
				this->left = NULL;
				this->right = NULL;
				this->token = Token(EOF_, "NOOPEARTOR");
			}
			NodeType getType(){
				return NOOPERATOR;
			}
};
class Program : public AST
{
	public:
			Program(){}
			Program(std::string name, AST* left){
				this->name = name;
				this->token = Token(EOF_, "PROGRAM");
				this->left = left;
				this->right = NULL;
			}
			NodeType getType(){
				return PROGRAMNODE;
			}
			std::string name;
};
class Block : public AST
{
	public: 
			Block(){}
			Block(AST* compound_statement){
				this->left = compound_statement;
				this->token = Token(EOF_, "BLOCK");
				this->right = NULL;
			}
			NodeType getType(){
				return BLOCK;
			}
			std::vector<std::vector<AST*> > declarations;
};
class VarDecl : public AST
{
	public: 
			VarDecl(){}
			VarDecl(AST* var_node, AST* type_node)
			{
				this->left = var_node;
				this->right = type_node;
				this->token = Token(EOF_, "VARDECL");
			}
			NodeType getType(){
				return VARDECL;
			}
};
class Type : public AST
{
	public: 
			Type(){}
			Type(Token token)
			{
				this->left = NULL;
				this->token = token;
				this->right = NULL;
			}
			NodeType getType(){
				return TYPE;
			}
			std::string name;
};
class ProcedureDecl : public AST
{
	public:
			ProcedureDecl(){}
			ProcedureDecl(std::string name, AST* block_node)
			{
				this->name = name;	
				this->left = block_node;
				this->right = NULL;
				this->token = Token(EOF_, "PROCEDURE"); 
			}
			NodeType getType(){
				return PROCEDURENODE;
			}
			std::string name;
					
};
#endif
