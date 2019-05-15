#ifndef _SYMBOL_H_
#define _SYMBOL_H_

#include <list>

/********** Type System ************/
class Type;


class Type
{
public:
	virtual ~Type(void) {}
};

class ArithmType : public Type
{
public:
	enum {
		TBOOL = 0, TCHAR, TUCHAR,
		TSHORT, TUSHORT, TINT, TUINT,
		TLONG, TULONG, TLLONG, TULLONG,
		TFLOAT, TDOUBLE, TLDOUBLE,
		TFCOMPLEX, TDCOMPLEX, TLDCOMPLEX, TSIZE
	};
	virtual ~ArithmType(void) {}

	bool IsBool(void) const {
		return TBOOL == _tag;
	}

	bool IsInteger(void) const {
		return (TBOOL <= _tag) && (_tag <= TULLONG);
	}

	bool IsReal(void) const {
		return (TFLOAT <= _tag) && (_tag <= TLDOUBLE);
	}

	bool IsComplex(void) const {
		return (TFCOMPLEX <= _tag) && (_tag <= TLDCOMPLEX);
	}
protected:
	ArithmType(int tag) : _tag(tag), Type(CalcWidth(tag)) {
		assert(TBOOL <= tag && tag <= TLDCOMPLEX);
	}

private:
	int _tag;
	static int CalcWidth(int tag);
};
class DerivedType : public Type
{
public:
	Type* Derived(void) {
		return _derived;
	}

	const Type* Derived(void) const {
		return _derived;
	}
protected:
	DerivedType(Type* derived, int width)
		: _derived(derived), Type(witdh) {}

	Type* _derived;
};
class PointerType : public DerivedType
{

};
class ArrayType : public PointerType
{

};
class FuncType : public DerivedType
{

};

class StructUnionType : public Type
{

};
class EnumType : public Type
{

};

class Variable Symbol;

class Env
{

};
