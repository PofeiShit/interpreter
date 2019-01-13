#include "interpreter.h"
int main()
{
		std::string input = 
				" \
				BEGIN  \
				BEGIN  \
				number := 2; \
				a := number; \
				b := 10 * a + 10 * number / 4; \
				c := a - - b; \
				END; \
				x := 11; \
				END. \
				";
		//std::cout << "spi> ";
		//getline(std::cin, input);
		Lexer lexer(input);
		Parser parser(lexer);
		Interpreter interpreter(parser);
		interpreter.interpret();
		for(std::map<std::string, int>::iterator itr = interpreter.GLOBAL_SCOPE.begin(); itr != interpreter.GLOBAL_SCOPE.end(); itr++){
			std::cout << itr->first << ":" << itr->second << std::endl;
		}
		return 0;
}
