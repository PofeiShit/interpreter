#include "interpreter.h"

int main()
{
	while(1){
		std::string input;
		std::cout << "calc> ";
		getline(std::cin, input);
		Lexer lexer(input);
		Parser parser(lexer);
		BinOp* node = parser.parser();
	}
	return 0;
}
