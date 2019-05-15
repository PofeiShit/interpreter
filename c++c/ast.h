#ifndef _AST_H_
#define _AST_H_
#include <list>
#include "symbol.h"
#include "token.h"
class ASTNode;
typedef ASTNode ExtDecl;
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

/********** Expr ***************/
class Expr : public ASTNode
{
public 
	virtual ~Expr(void) {}
    
    Type* Ty(void){
		return _ty;
	}
protected:
	explicit Expr(Type* type) : _ty(type) {}
	Type* _ty;
};
/********* Identifier **********/
class Variable : public Expr
{
public:
	static const int TYPE = -1;
	static const int VAR = 0;
	~Variable(void) {}

	// of course a variable is a lvalue expression
	virtual bool IsLVal(void) const {
		return true;
	}

	/*
	bool operator==(const Varibale& other) const {
		return _offset == other._offset && *_ty == *other._ty;
	}

	bool operator!=(const Varibale& other) const {
		return !(*this == other);
	}
	*/
protected:
	Variable(Type *type, int offset = VAR)
		: Expr(type), _offset(offset) {}
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
	Constant(ArithmType* type, size_t val)
		: Expr(type), _val(val) {}

	size_t _val;
};

class AssignExpr : public ASTNode
{
public:
	~AssignExpr(void) {}
};
class BinaryOp : public Expr
{
public:
	~BinaryOp(void) {}
protected:
	BinaryOp(Type* type, int op, Expr* lhs, Expr* rhs)
		: Expr(type), _op(op), _lhs(lhs), _rhs(rhs) {}

	int _op;
	Expr* _lhs;
	Expr* _rhs;
};
class UnaryOp : public Expr
{
public:
	~UnaryOp(void) {}
	// TODO:like '++i' is lvalue, but '~i' is not lvalue
	virtual bool IsLVal(void) const {
		// only deref('*') op is lvalue
		return (Token::DEREF == _op);
	}
protected:
	UnaryOp(Type* type, int op, Expr* expr)
		: Expr(type), _expr(expr) {
		switch (op) {
		case Token::PREFIX_INC: case Token::PREFIX_DEC:
		case Token::ADDR: case Token::DEREF: case Token::PLUS:
		case Token::MINUS: case '~': case '!':
			break;
		default: assert(false);
		}

		int _op;
		Expr* _expr;
};
class FuncCall : public Expr
{
public:
	~FuncCall(void) {}

protected:
	FuncCall(Type* type, Expr* caller, std::list<Expr*> args)
		: Expr(type), _caller(caller), _args(args) {}

	Expr* _caller;
	std::list<Expr*> _args;
};

class TranslationUnit : public ASTNode
{
public:
	virtual ~TranslationUnit(void) {
		auto iter = _extDecls.begin();
		for (; iter != _extDecls.end9); iter++_
			delete *iter;
	}

};
#endif
