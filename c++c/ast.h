#ifndef _AST_H_
#define _AST_H_
#include <list>
#include "symbol.h"
#include "token.h"
class ASTNode;
class Expr;
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
