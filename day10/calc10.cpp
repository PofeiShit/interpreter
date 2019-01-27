#include "interpreter.h"
int main()
{
	std::string input = 
		" \
		PROGRAM Part10; \
		VAR \
		number     : INTEGER; \
		a, b, c, x : INTEGER; \
		y          : REAL; \
		\
		BEGIN {Part10} \
		BEGIN \
		number := 2; \
		a := number; \
		b := 10 * a + 10 * number DIV 6; \
		c := a - - b; \
		END; \
		x := 11; \
		y := 20 / 7 + 3.14; \
		{ writeln('a = ', a); } \
	{ writeln('b = ', b); } \
	{ writeln('c = ', c); } \
	{ writeln('number = ', number); } \
	{ writeln('x = ', x); } \
	{ writeln('y = ', y); } \
	END.  {Part10} \
		";
	//std::cout << "spi> ";
	//getline(std::cin, input);
	Lexer lexer(input);
	Parser parser(lexer);
	Interpreter interpreter(parser);
	interpreter.interpret();
	for(std::map<std::string, std::string>::iterator itr = interpreter.GLOBAL_SCOPE.begin(); itr != interpreter.GLOBAL_SCOPE.end(); itr++){
		std::cout << itr->first << ":" << itr->second << std::endl;
	}
	return 0;
}
