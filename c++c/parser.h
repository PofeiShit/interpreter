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

	FuncCall* ParseFuncCall(Expr* caller);
	
	Expr* ParseUnaryExpr(void);
	Constant* ParseSizeofOperand(void);
	Constant* ParseAlignofOperand(void);
	UnaryOp* ParseAddrOperand(void);

	Type* ParseTypeName(void);

	Expr* ParseCastExpr(void);
	BinaryOp* ParseCommaExpr(void);
	BinaryOp* ParseAssignExpr(void);
private:
	Token* Next(void) {
		return _lexer->Get();
	}
private:
	Lexer* _lexer;
	Env* _topEnv;
	std::stack<Token*> _buf;
}
#endif
