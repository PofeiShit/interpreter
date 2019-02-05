#include "symbol01.h"
void symbol01()
{
	std::string text = "\
	program SymTab1; \
		var x, y : integer; \
	begin \
		  \
	end.  \
	";
	Lexer lexer(text);
	Parser parser(lexer);
	AST* tree = parser.parser();

	SymbolTable symtab;
	Symbol* int_type = new BuiltinTypeSymbol("INTEGER");
	symtab.insert(int_type);

	Symbol* var_x_symbol = new VarSymbol("x", int_type->name);
	symtab.insert(var_x_symbol);

	Symbol* var_y_symbol = new VarSymbol("y", int_type->name);
	symtab.insert(var_y_symbol);

	symtab.showSymbol();
}



