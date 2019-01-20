#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "parser.h"
class Interpreter
{
	public:
		Parser parser;
		template<typename T>
		std::map<std::string, T> GLOBAL_SCOPE;

	public:
		Interpreter();
		Interpreter(const Parser &parser);
		~Interpreter();
		template<typename T>
		T visit(Num *node);
		template<typename T>
		T visit(BinOp *node);
		template<typename T>
		T visit(UnaryOperator *node);
		void visit(Compound *node);
		void visit(Assign *node);
		template<typename T>
		T visit(Variable *node);
		void visit(NoOperator *node);
		void visit(Program* node);
		void visit(Block *node);
		void visit(VarDecl *node);
		void visit(Type *node);
		void interpret();
		void error();

};
#endif
