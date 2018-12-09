#include "interpreter.h"

int main()
{
	while(1){
		std::string input;
		std::cout << "calc> ";
		getline(std::cin, input);
		Interpreter interpreter = Interpreter(input);	
		int result = interpreter.expr();
		std::cout << result << std::endl;

	}
	return 0;
}
