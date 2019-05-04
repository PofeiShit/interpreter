#include <iostream>
#include "lexer.h"

using namespace std;

int main()
{
	Lexer lexer("unittest.c");	
	lexer.Tokenize();
	return 0;
}
