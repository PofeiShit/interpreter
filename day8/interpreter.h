#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "parser.h"
class NodeVisitor
{
	public:
			virtual int visit(Num *node) = 0;
			virtual int visit(BinOp *node) = 0;
			virtual int visit(UnaryOperator* node) = 0;

};
class Interpreter : public NodeVisitor
{
	public:
		Parser parser;

	public:
		Interpreter();
		Interpreter(const Parser &parser);
		~Interpreter();
		int visit(Num *node);
		int visit(BinOp *node);
		int visit(UnaryOperator *node);
		int interpret();

};
#endif
