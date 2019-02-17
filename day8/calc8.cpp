#include "interpreter.h"
#include "test_calc.h"
int main()
{
#ifdef UNIT_TEST
		test();
#endif
	while(1){
		std::string input;
		std::cout << "spi> ";
		getline(std::cin, input);
		Lexer lexer(input);
		Parser parser(lexer);
		Interpreter interpreter(parser);
	   	int result = interpreter.interpret();
		std::cout << input << " = " << result << std::endl;
	}
	return 0;
}
