#include "symbol06.h"

void symbol06()
{
	std::string text = "\
	program SymTab6; \
		var x, y : integer; \
		var y : real; \
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

