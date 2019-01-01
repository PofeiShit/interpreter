#ifndef NUM_H_
#define NUM_H_

#include "ast.h"
class Num : public AST
{
		public:
				Token token;
				int value;
		public:
				Num(Token token);
				~Num();

};
#endif
