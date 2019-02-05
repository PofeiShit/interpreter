#include "symbol01.h"

int main()
{
	std::string text = "\
	program SymTab1; \
		var x, y : integer; \
	begin \
		  \
	end.  \
	"
	Lexer lexer(text);
	Parser parser(lexer);
	AST* tree = parser.parser();

	SymbolTable symtab;
	BuiltinTypeSymbol int_type("INTEGER");
	symtab.insert(static_cast<Symbol*>(&int_type));

	VarSymbol var_x_symbol("x", static_cast<Symbol*>(&int_type));
	symtab.insert(var_x_symbol);

	VarSymbol var_y_symbol("y", static_cast<Symbol*>(&int_type));
	symtab.insert(var_y_symbol);

	symtab.showSymbol();
	return 0;
}



