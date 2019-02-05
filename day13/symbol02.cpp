#include "symbol02.h"

void symbol02()
{
	std::string text = "\
	program SymTab2; \
		var x, y : integer; \
	begin \
		  \
	end.  \
	";
	Lexer lexer(text);
	Parser parser(lexer);
	AST* tree = parser.parser();

	SemanticAnalyzer semantic_analyzer;
	semantic_analyzer.visit(static_cast<Program*>(tree));
	semantic_analyzer.symbol_table.showSymbol();
}



