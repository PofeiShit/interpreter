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
				int getValue(){
					return atoi(token.value.c_str());
				}
				NodeType getType(){
					return NUM;
				}
				~Num(){}

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
			this->token = Token(EOF_, "");
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
				this->token = Token(EOF_, "");
			}
			NodeType getType(){
				return NOOPERATOR;
			}
};
#endif
