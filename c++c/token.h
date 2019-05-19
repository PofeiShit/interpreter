#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <unordered_map>
#include <cassert>
#include <cstring>
class Token
{
	friend class Lexer;
public:
	enum {
		/* punctuators */
		LPAR = '(',
		RPAR = ')',
		ADD = '+',
		SUB = '-',
		MUL = '*',
		DIV = '/',
		OR = '|',
		AND = '&',
		LESS = '<',
		GREAT = '>',
		EQUAL = '=',
		DOT = '.',
		MOD = '%',
		LBRACE = '{',
		XOR = '^',
		NOT = '!',
		COND = '?',
		SHARP = '#',

		DSHARP = 128, // ##
		PTR_OP,
		INC_OP,
		DEC_OP,
		LEFT_OP,
		RIGHT_OP,
		LE_OP,
		GE_OP,
		EQ_OP,
		NE_OP,
		AND_OP,
		OR_OP,
		
		MUL_ASSIGN,
		DIV_ASSIGN,
		MOD_ASSIGN,
		ADD_ASSIGN,
		SUB_ASSIGN,
		LEFT_ASSIGN,
		RIGHT_ASSIGN,
		AND_ASSIGN,
		XOR_ASSIGN,
		OR_ASSIGN,
	
		ELLIPSIS,
		/* punctuators end */
	    /* key words */
		AUTO,
		
		THREAD_LOCAL,
		/* key words end */
		IDENTIFIER,
		CONSTANT,
		STRING_LITERAL,
        
		IGNORE,
		INVALID,
		END,
		NOTOK = -1,
	};
	int Tag(void) const {
		return _tag;
	}
	int Line(void) const {
		return _line;
	}
	int Column(void) const {
		return _column;
	}
	const char* FileName(void) const {
		return _fileName;
	}
	void SetVal(const char* begin, const char* end)
	{
		size_t size = end - begin;
		auto val = new char[size + 1];
		memcpy(val, begin, size);
		val[size] = 0;
		_val = val;
	}
	static bool IsKeyWord(int tag)
	{
		return AUTO <= tag && tag <= THREAD_LOCAL;
	}
	bool IsKeyWord(void) const {
		return IsKeyWord(_tag);
	}
	bool IsPunctuator(void) const {
		return LPAR <= _tag && _tag <= ELLIPSIS;
	}
	bool IsIdentifier(void) const {
		return IDENTIFIER == _tag;
	}
	bool IsEOF(void) const {
		return _tag == Token::END;
	}
	bool IsTypeQual(void) const {
		switch (_tag) {
		case CONST: case RESTRICT:
		case VOLATILE: case ATOMIC:
			return true;
		default: return false;
		}
	}
	bool IsTypeSpec(void) const {
		switch (_tag) {
		case VOID: case CHAR: case SHORT:
		case INT: case LONG: case FLOAT:
		case DOUBLE: case SINGED: case UNSIGNED:
		case BOOL: case COMPLEX: case IMAGINARY:
		case STRUCT: case UNION: case ENUM: case ATOMIC:
			return true;
		default: return false;
		}
	}
private:
	int _tag;
	int _line;
	int _column;
	const char* _fileName;
	const char* _val;
	static const std::unordered_map<std::string, int> _kwTypeMap;
	static const std::unordered_map<int, const char*> _TagLexemeMap;
private:
	Token(int tag, const char* fileName = nullptr, int line = 1, int column = 1, const char* begin = nullptr, const char* end = nullptr) : _tag(tag), _fileName(fileName), _line(line), _column(column){
		if (nullptr == begin) {
			assert(IsPunctuator() || IsKeyWord() || IsEOF());
			_val = _TagLexemeMap.at(tag);
		} else {
			SetVal(begin, end);
		}
	}
	// Token::NOTOK represents not a kw
	static int KeyWordTag(const char* begin, const char* end)
	{
		std::string key(begin, end);
		auto kwIter = _kwTypeMap.find(key);
		if (_kwTypeMap.end() == kwIter)
				return Token::NOTOK; //not a key word type
		return kwIter->second;
	}
};
#endif
