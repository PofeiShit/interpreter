#include "expr.h"

BinaryOp* BinaryOp::TypeChecking(void)
{
	switch (_op) {
		case '[': return SubScriptingOpTypeChecking();
		case '*': case '/': case '%': return MultiOpTypeChecking();
		case '+': case '-': return AdditiveOpTypeChecking();	  
		case Token::LEFT_OP: case Token::RIGHT_OP: return ShiftOpTypeChecking();	
		case '<': case '>': case Token::LE_OP: case Token::GE_OP: return RelationalOpTypeChecking();
		case Token::EQ_OP: case Token::NE_OP: return EqualityOpTypeChecking();
		case '&': case '^': case '|': return BitwiseOpTypeChecking();
		case Token::AND_OP: case Token::OR_OP: return LogicalOpTypeChecking();
		case '=': return AssignOpTypeChecking();
		default: assert(0); return nullptr;
	}
}
BinaryOp* BinaryOp::SubScriptingOpTypeChecking(void)
{
	auto lhsType = _lhs->Ty()->ToPointerType();
	if (nullptr == lhsType)
		Error("an pointer expected");
	if (!_rhs->Ty()->IsInteger())
		Error("the operand of [] should be integer");

	// the type of [] operator is the type of the pointer pointed to 
	_ty = lhsType->Derived();
	return this;
}

