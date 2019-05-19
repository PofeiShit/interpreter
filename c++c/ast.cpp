#include "ast.h"
#include "expr.h"

ConditionalOp* TranslationUnit::NewConditionalOp(Expr* cond, Expr* exprTrue, Expr* exprFalse)
{
	return (new ConditionalOp(cond, exprTrue, exprFalse))->TypeChecking();
}
BinaryOp* TranslationUnit::NewBinaryOp(int op, Expr* lhs, Expr* rhs)
{

}
