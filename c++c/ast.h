#ifndef _AST_H_
#define _AST_H_
#include <list>
#include "symbol.h"
#include "token.h"
class ASTVisitor;
class ASTNode;
typedef ASTNode ExtDecl;
class Expr;
class BinaryOp;
class ConditionalOp;
class UnaryOp;

class FuncCall;
class Variable;
class Constant;
class AssignExpr;
/*********** AST Node ************/
class ASTNode 
{
public:
	virtual ~ASTNode(void){}

protected:
	ASTNode(void){}
};

/*********** Declaration **********/
class FuncDef : public ExtDecl
{

};
class Decl : public ExtDecl
{

};


class TranslationUnit : public ASTNode
{
public:
	virtual ~TranslationUnit(void) {
		auto iter = _extDecls.begin();
		for (; iter != _extDecls.end9); iter++_
			delete *iter;
	}
	/************* Binary Operator **************/
	static BinaryOp* NewBinaryOp(Expr* lhs, Expr* rhs);
	static BinaryOp* NewMemberRefOp(int op, Expr* lhs, const char* rhsName);
	static ConditionalOp* NewConditionalOp(Expr* cond, Expr* exprTrue, Expr* exprFalse);
	static FuncCall* NewFuncCall(Expr* designator, const std::list<Expr*>& args);
	static Variable NewVariable(Type* type, int offset = );
	static Constant* NewConstant(ArithmType* type, size_t val);
	static Constant* NewConstant(PointerType* type);
	
	static UnaryOp* NewUnaryOp(int op, Expr* operand, Type* type = nullptr);
pivate:
	TranslationUnit(void) {}

	std::list<ExtDecl*> _extDecls;
};
#endif
