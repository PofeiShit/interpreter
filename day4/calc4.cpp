#include "interpreter.h"
#include "test_calc4.h"
#define UNIT_TEST 1
int main()
{
#ifdef UNIT_TEST
	test();
#endif
	while(1){
		std::string input;
		std::cout << "calc> ";
		getline(std::cin, input);
		Lexer lexer(input);
		Interpreter interpreter = Interpreter(lexer);	
		int result = interpreter.expr();
		std::cout << result << std::endl;

	}
	return 0;
}
