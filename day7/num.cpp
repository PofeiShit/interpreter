#include "num.h"

Num::Num(Token token):token(token)
{
	value = atoi(token.value.c_str());
}
Num::~Num(){

}
