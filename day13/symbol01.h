#ifndef SYMBOL01_H_
#define SYMBOL01_H_
#include <map>
#include "symbol.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"
class SymbolTable
{
	public:
			std::map<std::string, Symbol*> _symbols;
			SymbolTable()
			{
				init_builtins();
			}

	public:
			void init_builtins()
			{
				define(static_cast<Symbol*>(new BuiltinTypeSymbol("INTEGER")));
				define(static_cast<Symbol*>(new BuiltinTypeSymbol("REAL")));
			}
			void showSymbol()
			{
				std::cout << "符号表中的内容:\n";
				std::cout << "---------------\n";	
				for(auto itr = _symbols.begin(); itr != _symbols.end(); itr++)
				std::cout << itr->first << ":";
				itr->second.print();
			}
			void insert(Symbol* symbol){
				std::cout << "insert: " << symbol->name << std::endl;
				_symbols[symbol->name] = symbol;
			}
};
#endif
