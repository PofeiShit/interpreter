#include "symbol04.h"

void symbol04()
{
	std::string text = "\
	program SymTab4; \
		var x, y : integer; \
	begin \
		 x := x + y; \ 
	end.  \
	";
	Lexer lexer(text);
	Parser parser(lexer);
	AST* tree = parser.parser();

	SemanticAnalyzer semantic_analyzer;
	semantic_analyzer.visit(static_cast<Program*>(tree));
	semantic_analyzer.symbol_table.showSymbol();
}

