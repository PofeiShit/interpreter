#ifndef SEMANTIC_H_
#define SEMANTIC_H_
#include "interpreter.h"
#include "symbol.h"
class SemanticAnalyzer : public NodeVisitor
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
