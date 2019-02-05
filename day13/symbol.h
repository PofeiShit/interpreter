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
			virtual void print() = 0;
};
class BuiltinTypeSymbol : public Symbol
{
	public:
			BuiltinTypeSymbol(std::string _name){
				this->name = _name;
			    this->symbol_type = "None";
			}	
std::string getName(){
				return name;
			}
			void print(){
				std::cout << "<BuiltinTypeSymbol(name='" << this->name << "')>\n";
			}
};
class VarSymbol : public Symbol
{
	public:
			VarSymbol(std::string _name, std::string _type){
				this->name = _name;
				this->symbol_type = _type;
			}
			
			std::string getName(){
				return name + ":" + symbol_type;
			}
			void print(){
				std::cout << "<VarSymbol(name='" << this->name << "', type='" << this->symbol_type << "')>\n";
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
			void init_builtins()
			{
				insert(static_cast<Symbol*>(new BuiltinTypeSymbol("INTEGER")));
				insert(static_cast<Symbol*>(new BuiltinTypeSymbol("REAL")));
			}
			void showSymbol()
			{
				std::cout << "符号表中的内容:\n";
				std::cout << "---------------\n";	
				for(auto itr = _symbols.begin(); itr != _symbols.end(); itr++){
					std::cout << itr->first << ":";
					itr->second->print();
				}
			}
			void insert(Symbol* symbol){
				std::cout << "insert: " << symbol->name << std::endl;
				_symbols[symbol->name] = symbol;
			}
			Symbol* lookUp(std::string _name){
					std::cout << "lookup: " << _name << std::endl;
					if(_symbols.find(_name) != _symbols.end())
						return _symbols[_name];
					
					return NULL;
			}
};
class NodeVisitor;
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
		void visit(ProcedureDecl *node);

	public:
		SymbolTable symbol_table;

};
#endif
