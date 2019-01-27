#ifndef INTERPRETER_H_
#define INTERPRETER_H_
#include "parser.h"
extern std::map<std::string, std::string> VAR_TYPES;

class NodeVisitor
{
	public:
			virtual void visit(NoOperator *node) = 0;
			virtual void visit(Assign* node) = 0;
			virtual void visit(Compound* node) = 0;
			virtual void visit(Program* node) = 0;
			virtual void visit(Block* node) = 0;
			virtual void visit(VarDecl* node) = 0;
			virtual void visit(Type* node) = 0;
};
class Interpreter : public NodeVisitor
{
	public:
		Parser parser;
		AST* tree;
		std::map<std::string, std::string> GLOBAL_SCOPE;

	public:
		Interpreter();
		Interpreter(const Parser &parser);
		Interpreter(AST* tree);
		~Interpreter();
		template<typename T> T visit(Num *node);
		template<typename T> T visit(BinOp *node);
		template<typename T> T visit(UnaryOperator *node);
		template<typename T> T visit(Variable *node);
		void visit(Assign *node);
		void visit(Compound *node);
		void visit(NoOperator *node);
		void visit(Program* node);
		void visit(Block *node);
		void visit(VarDecl *node);
		void visit(Type *node);
		void interpret();
		void error();

};
#endif
