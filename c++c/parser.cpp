#include "parser.h"
using namespace std;

Expr* Parser::ParseExpr(void)
{
	return ParseCommaExpr();
}
Expr* Parser::ParseCommaExpr(void)
{
	auto lhs = ParseAssignExpr();
	while (Try(',')) {
		auto rhs = ParseAssignExpr();
		lhs = TranslationUnit::NewCommaOp(lhs, rhs);
	}
	return lhs;
}
BinaryOp* Parser::ParseAssignExpr(void)
{
	return nullptr;
}
Expr* Parser::ParsePrimaryExpr(void)
{
	if (Peek()->IsKeyWord()) // can never be a expression
			return nullptr;
	
	auto tok = Next();
	if (tok->IsEOF()) return nullptr;
	if (tok->Tag() == '(') {
		auto expr = ParseExpr();
		Expect(')');
		return expr;
	}
	if (tok->IsIdentifier()) {
		// TODO: create a expreesion node with symbol
	} else if (tok->IsConstant()) {
		return ParseConstant(tok);
	}
}
Expr* Parser::ParseConstant(const Token* tok)
{
	assert(tok->IsConstant());
	return nullptr;
}
Expr* Parser::ParseUnaryExpr(void)
{
	auto tok = Next();
	switch (tok->Tag()) {
	case Token::ALIGNOF: return ParseAlignofOperand();
	case Token::SIZEOF: return ParseSizeofOperand();
	case Token::INC_OP: case Token::DEC_OP: return ParsePrefixIncDec(tok->Tag());
	
	case '&': case '*': case '+':
	case '-': case '~': case '!':
		// 
	default:
		
	}
}
Expr* Parser::ParseCastExpr(void)
{
	atuo tok = Next();
	if (tok->Tag() == '(' && IsType(Peek())) {
		auto desType = ParseTypeName();
		Expect(')');
		auto operand = ParseCastExpr();
		return TranslationUnit::NewCastOp(operand, desType);
	}
	return PutBack(), ParseUnaryExpr();
}
Expr* Parser::ParseMultiplicativeExpr(void)
{
	auto lhs = ParseCastExpr();
}
Expr* Parser::ParseAdditiveExpr(void)
{
	auto lhs = ParseMultiplicativeExpr();
}
Expr* Parser::ParseShiftExpr(void)
{
	auto lhs = ParseAdditiveExpr();
};
Expr* Parser::ParseRelationalExpr(void)
{
	auto lhs = ParseShiftExpr();
}
Expr* Parser::ParseEqualityExpr(void)
{
	auto lhs = ParseRelationalExpr();
}
Expr* Parser::ParseBitwiseAndExpr(void)
{
	auto lhs = ParseEqualityExpr();
}
Expr* Parser::ParseBitwiseXorExpr(void)
{
	auto lhs = ParseBitwiseAndExpr();
}
Expr* Parser::ParseBitwiseOrExpr(void)
{
	auto lhs = ParseBitwiseXorExpr();
}
Expr* Parser::ParseLogicalAndExpr(void)
{
	auto lhs = ParseBitwiseOrExpr();
}
Expr* Parser::ParseLogicalOrExpr(void)
{
	auto lhs = ParseLogicalAndExpr();
}
Expr* Parser::ParseconditionalExpr(void)
{
	auto cond = ParseLogicalOrExpr();
}
Expr* Parser::ParseAssignExpr(void)
{
}
