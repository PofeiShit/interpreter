#include "interpreter.h"
#include "symbol.h"
int main()
{
	std::string input = 
		" \
		PROGRAM Part11; \
		VAR \
			number : INTEGER; \
			a, b   : INTEGER; \
			y      : REAL; \
		BEGIN {Part11} \
			number := 2; \
			a := number; \
			b := 10 * a + 10 * number DIV 4; \
			y := 20 / 7 + 3.14; \
		END.  {Part10} \
		";
	//std::cout << "spi> ";
	//getline(std::cin, input);
	Lexer lexer(input);
	Parser parser(lexer);
	AST* tree = parser.parser();
	symtab_builder = SymbolTableBuilder();	
	symtab_builder.visit(tree);
	std::cout << "符号表中的内容" << symtab_builder.symbol_table << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "开始解释代码..." << std::endl;
	Interpreter interpreter(tree);
	interpreter.interpret();
	std::cout << "全局存储中的内容:" << std::endl;
	for(std::map<std::string, std::string>::iterator itr = interpreter.GLOBAL_SCOPE.begin(); itr != interpreter.GLOBAL_SCOPE.end(); itr++){
		std::cout << itr->first << ":" << itr->second << std::endl;
	}
	return 0;
}
