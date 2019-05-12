#include <iostream>
#include "lexer.h"

using namespace std;

int main()
{
	Lexer lexer("unittest.c");	
	lexer.Tokenize();
	int result[] = {Token::PTR_OP, Token::DEC_OP, Token::SUB_ASSIGN, Token::SUB, Token::INC_OP, Token::ADD_ASSIGN, Token::ADD, Token::LEFT_ASSIGN};
	int n = sizeof(result) / sizeof(result[0]);
	for(int i = 0; i < n; ++i){
		Token* t = lexer.Get();
		printf("%d\t%d\n", result[i], t->Tag());
		assert(result[i] == t->Tag());
	}
	printf("token test pass\n");
	return 0;
}
