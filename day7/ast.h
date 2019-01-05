#ifndef AST_H_
#define AST_H_
#include "token.h"
class AST
{
		public:
				AST(){
				}
				virtual	~AST(){
				
				}
		public:
				AST* left;
				AST* right;
				Token token;

};
class Num : public AST
{
		public:
				Num(Token token){
					this->token = token;
					this->left = this->right = NULL;
				}
				int getValue(){
					return value;
				}
		private:
				int value;	

};
class BinOp : public AST
{
		public:
				BinOp(AST* left, Token _operator, AST* right)
				{
					this->token = _operator;
					this->left = left;
					this->right = right;
				}

};

#endif
