#ifndef AST_H_
#define AST_H_
#include "token.h"
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

#endif
