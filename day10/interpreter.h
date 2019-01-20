#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "parser.h"
class NodeVisitor
{
	public:
			virtual int visit(Num *node) = 0;
			virtual int visit(BinOp *node) = 0;
			virtual int visit(UnaryOperator* node) = 0;
			virtual void visit(Compound *node) = 0;
			virtual void visit(Assign *node) = 0;
			virtual int visit(Variable *node) = 0;
			virtual void visit(NoOperator *node) = 0;

};
class Interpreter : public NodeVisitor
{
	public:
		Parser parser;
		std::map<std::string, int> GLOBAL_SCOPE;

	public:
		Interpreter();
		Interpreter(const Parser &parser);
		~Interpreter();
		int visit(Num *node);
		int visit(BinOp *node);
		int visit(UnaryOperator *node);
		void visit(Compound *node);
		void visit(Assign *node);
		int visit(Variable *node);
		void visit(NoOperator *node);
		int interpret();
		void error();

};
#endif
