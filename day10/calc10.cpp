#include "interpreter.h"
int main()
{
		std::string input = 
				" \
				PROGRAM Part10AST; \
				VAR \
					a, b : INTEGER; \
					y 	 : REAL; \
				BEGIN  {Part10AST} \
				a := 2; \
				b := 10 * a + 10 * a DIV 4; \
				y := 20 / 7 + 3.14; \
				END. {Part10AST} \
				";
		//std::cout << "spi> ";
		//getline(std::cin, input);
		Lexer lexer(input);
		Parser parser(lexer);
		AST* node = parser.parser();
//		Interpreter interpreter(parser);
//		interpreter.interpret();
//		for(std::map<std::string, int>::iterator itr = interpreter.GLOBAL_SCOPE.begin(); itr != interpreter.GLOBAL_SCOPE.end(); itr++){
//			std::cout << itr->first << ":" << itr->second << std::endl;
		//}
		return 0;
}
