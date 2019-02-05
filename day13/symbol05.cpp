#include "symbol05.h"

void symbol05()
{
	std::string text = "\
	program SymTab5; \
		var x : integer; \
	begin \
		 x := y; \ 
	end.  \
	";
	Lexer lexer(text);
	Parser parser(lexer);
	AST* tree = parser.parser();

	SemanticAnalyzer semantic_analyzer;
	semantic_analyzer.visit(static_cast<Program*>(tree));
	semantic_analyzer.symbol_table.showSymbol();
}

