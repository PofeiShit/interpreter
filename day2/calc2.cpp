#include "interpreter.h"
#include "test_calc2.h"
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
		Interpreter interpreter = Interpreter(input);	
		int result = interpreter.expr();
		std::cout << result << std::endl;

	}
	return 0;
}
