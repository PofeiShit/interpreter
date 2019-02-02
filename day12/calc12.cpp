#include "interpreter.h"
#include "symbol.h"
#include <fstream>
int main(int argc, char **argv)
{
		if(argc < 2){
			fprintf(stderr, "参数太少\n");
			return -1;
		}
		std::ifstream fin(argv[1]);
		std::string input(""), s;
		while(getline(fin, s)){
			input += s;
		}
		Lexer lexer(input);
		Parser parser(lexer);
		AST* tree = parser.parser();
		SymbolTableBuilder symtab_builder;	
		symtab_builder.visit(static_cast<Program*>(tree));
		std::cout << "符号表中的内容:\n";  
		symtab_builder.symbol_table.showSymbol();
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
