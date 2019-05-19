#ifndef _PARSER_H_
#define _PARSER_H_
#include "lexer.h"
class Env;
class Parser
{
public:
	explicit Parser(Lexer* lexer) : _lexer(lexer) {}

	~Parser(void) {
		delete _lexer;
	}
	Expr* ParseConstant(const Token* tok);
	Expr* ParseString(const Token* tok);
	Expr* ParseGeneric(void);
	/********* Declaration ***************/
	Decl* ParseFuncDef(void);
	Expr* ParseDecl(void);
	/******** Expression *********/
	Expr* ParseExpr(void);
	Expr* ParsePrimaryExpr(void);

	Expr* ParsePostfixExpr(void);
	Expr* ParsePostfixExprTail(Expr* primExpr);
    SubSrciptingOp* ParseSubScripting(Expr* pointer);
	MemberRefOp* ParseMemberRef(int tag, Expr* lhs);
	UnaryOp* ParsePostfixIncDec(int tag, Expr* expr);
	FuncCall* ParseFuncCall(Expr* caller);
	
	Expr* ParseUnaryExpr(void);
	Constant* ParseSizeofOperand(void);
	Constant* ParseAlignofOperand(void);
	UnaryOp* ParsePrefixIncDec(int tag);
	UnaryOp* ParseAddrOperand(void);

	Type* ParseTypeName(void);
	Expr* ParseCastExpr(void);
	Expr* ParseMultiplicativeExpr(void);
	Expr* ParseAdditiveExpr(void);
	Expr* ParseShiftExpr(void);
	Expr* ParseRelationalExpr(void);
	Expr* ParseEqualityExpr(void);
	Expr* ParseBitwiseAndExpr(void);
	Expr* ParseBitwiseXorExpr(void);
	Expr* ParseBitwiseOrExpr(void);
	Expr* ParseLogicalAndExpr(void);
	Expr* ParseLogicalOrExpr(void);
	Expr* ParseConditionalExpr(void);
	Expr* ParseCommaExpr(void);
	Expr* ParseAssignExpr(void);
private:
	// 如果当前token符合参数，返回true,并consume一个token
	// 如果与tokTag不符，则返回false,并且不consume token
	bool Try(int tokTag) {
		auto tok = Next();
		if (tok->Tag() == tokTag)
				return true;
		PutBack();
		return false;
	}
	// 返回当前token,并前移
	Token* Next(void) {
		return _lexer->Get();
	}
	Token* Peek(void) {
		auto tok = _lexer->Peek();
		return tok;
	}
	void PutBack(void) {
		_lexer->Unget();
	}
	bool IsType(const Token* tok) {
		if (tok->IsTypeQual() || tok->IsTypeSpec()) 
			return true;
		return (tok->IsIdentifier() && nullptr != _topEnv->FindType(tok->Val()));
	}
private:
	Lexer* _lexer;
	Env* _topEnv;
	std::stack<Token*> _buf;
}
#endif
