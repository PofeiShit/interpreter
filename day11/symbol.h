#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include <string>
#include <map>
#include "interpreter.h" 
class Symbol
{
	public:
			std::string name;
			std::string symbol_type;
	public:
			virtual std::string getName() = 0;
};
class BuiltinTypeSymbol : public Symbol
{
	public:
			BuiltinTypeSymbol(std::string _name):name(_name), symbol_type(""){}
			
			std::string getName(){
				return name;
			}
};
class VarSymbol : public Symbol
{
	public:
			VarSymbol(std::string _name, std::string _type):name(_name), symbol_type(_type){}
			
			std::string getName(){
				return name + ":" + _type;
			}
};
class SymbolTable
{
	public:
			std::map<std::string, Symbol*> _symbols;
			SymbolTable()
			{
				init_builtins();
			}

	public:
			void intit_builtins()
			{
				define(static_cast<Symbol*>(BuiltinTypeSymbol("INTEGER")));
				define(static_cast<Symbol*>(BuiltinTypeSymbol("REAL")));
			}
			void printSymbol(){
				
			}
			void define(const Symbol* symbol){
				std::cout << "define : " << symbol->name << std::endl;
				_symbols[symbol->name] = symbol;
			}
			Symbols* lookUp(std::string _name){
				std::cout << "look up : " << _name << std::endl;
				if(_symbols.find(_name) != _symbols.end())
					return _symbols[_name];
				else 
					return NULL;
			}
};
class SymbolTableBuilder : public NodeVisitor
{
	public:
		void visit(Num *node);
		void visit(BinOp *node);
		void visit(UnaryOperator *node);
		void visit(Variable *node);
		void visit(Assign *node);
		void visit(Compound *node);
		void visit(NoOperator *node);
		void visit(Program* node);
		void visit(Block *node);
		void visit(VarDecl *node);
		void visit(Type *node);

	public:
		Symbol *symbol_table;

};
#endif
