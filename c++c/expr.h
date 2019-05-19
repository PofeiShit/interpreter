#ifndef _EXPR_H_
#define _EXPR_H_

#include <cassert>
#include "ast.h"

/********* Expr ************/
class Expr : public ASTNode
{
public:
	virtual ~Expr(void) {}	

	Type* Ty(void) {
		return _Ty;
	}

	const Type* Ty(void) const {
		assert(nullptr != _ty)
			return _Ty;
	}

	virtual bool IsLVal(void) const = 0;
protected:
	Type* _ty;
};

/*********** Identifier **************/
class Variable : public Expr
{
public:
	static const int TYPE = -1;
	static const int VAR = 0;
	~Variable(void) {}
private:
	// the relative address
	int _offset;
};
// integer of floating
class Constant : public Expr
{
public:
	~Constant(void) {}
protected:
	size_t val;
};
class AssignExpr : public ASTNode
{
public:
	~AssignExpr(void) {}
};
class BinaryOp : public Expr
{
public:
	virtual ~BinaryOp(void) {}

protected:
	Expr* _lhs;
	Expr* _rhs;
}
class CommaOp : public BinaryOp
{
public:
	virtual ~CommaOp(void) {}
}
class SubScriptingOp : public BinaryOp
{
public:
	virtual ~SubScriptingOp(void) {}
protected:
	virtual SubScriptingOp* TypeChecking(void);
};
class UnaryOp : public Expr
{
public:
	virtual ~UnaryOp(void) {}

	// TODO: like '++i' is lvalue, but '~i' is not lvalue
	virtual bool IsLVal(void) const{
		/* only deref('*') op is lvalue;
		   so it's only deref with override this func */
		return false;
	}
protected:
	Expr* _operand;
};
class PostfixIncDecOp : public UnaryOp
{

};
class PrefixIncDecOp : public UnaryOp
{

};
class AddrOp : public UnaryOp
{

};
class CastOp : public UnaryOp
{

};
class FuncCall : public Expr
{

};

#endif
