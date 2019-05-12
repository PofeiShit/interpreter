#ifndef _LEXER_H_
#define _LEXER_H_
#include <vector>
#include <string>
#include <cstring>
#include "token.h"
class Lexer
{
public:
	Lexer(const char* path){
			if(!(ReadFile(path))){
					//
			}
			_line = 1;
			_column = 1;
			_tokBegin = _text;
			_tokEnd = _text;
			_tokTop = 0;
	}
	Token* Get(void) {
		assert(_tokTop < _tokBuf.size());
		return _tokBuf[_tokTop++];
	}
	void Tokenize(void);
private:
	static const int _maxSize = 1024 * 1024 * 64;
	const char* _fileName;
	const char* _text;
	int _line;
	int _column;
    const char* _tokBegin;
	const char* _tokEnd;

	size_t _tokTop;
	std::vector<Token*> _tokBuf;
	bool ReadFile(const char* fileName);
	const char* ParseName(const char* path);
	Token* NewToken(int tag, const char* _tokBegin = nullptr, const char* _tokEnd = nullptr) {
		return new Token(tag, _fileName, _line, _column, _tokBegin, _tokEnd);
	}
};
#endif
