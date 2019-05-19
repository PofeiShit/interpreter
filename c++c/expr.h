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
class ConditionalOp : public Expr
{
public:
	virtual ~ConditionalOp(void) {}
	virtual bool IsLVal(void) const { return false; }
protected:
	virtual ConditionalOp* TypeChecking(void);
};

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
	BinaryOp(int op, Expr* lhs, Expr* rhs)
		: Expr(nullptr), _op(op), _lhs(lhs), _rhs(rhs) {}
	virtual BinaryOp* TypeChecking(void);
	BinaryOp* SubScriptingOpTypeChecking(void);
	BinaryOp* MemberRefOpTypeChecking(const char* rhsName);
	BinaryOp* MultiOpTypeChecking(void);
	BinaryOp* AdditiveOpTypeChecking(void);
	BinaryOp* ShiftOpTypeChecking(void); 
	BinaryOp* RelationalOpTypeChecking(void);
	Expr* _lhs;
	Expr* _rhs;
}

/************* Unary Operator **********/
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
	UnaryOp(int op, Expr* operand, Type* type = nullptr)
		: Expr(type), _op(op), _operand(operand) {}
	
	virtual UnaryOp* TypeChecking(void);
	UnaryOp* IncDecOpTypeChecking(void);
	UnaryOp* AddrOpTypeChecking(void);

	int _op;
	Expr* _operand;
};
/*
class PostfixIncDecOp : public UnaryOp
{

};
class PrefixIncDecOp : public UnaryOp
{

};
class AddrOp : public UnaryOp
{
public:
	virtual ~AddrOp(void) {}
	AddrOp(Expr* operand) : UnaryOp(operand, nullptr) {}
	virtual AddrOp* TypeChecking(void);
};
class CastOp : public UnaryOp
{

};
*/
class FuncCall : public Expr
{

};

#endif
