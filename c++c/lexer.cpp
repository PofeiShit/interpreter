#include "lexer.h"
#include "error.h"
static inline bool IsDigit(char ch)
{
	return '0' <= ch && ch <= '9';
}
static inline bool IsLetter(char ch)
{
	return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || '_' == ch;
}
static inline bool IsHex(char ch)
{
	return ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F') ||
			IsDigit(ch);
}
static void ReadConstant(const char*& p)
{
	bool sawEP = false, sawSign = false;
	for (; 0 != p[0]; p++) {
		if (IsHex(p[0])) 
			continue;	
		switch (p[0]) {
			// case '0' ... '9'
			// case 'a' ... 'f': case 'A' ... 'F'
			case '.':
			case 'u': case 'U': case 'l': case 'L':	
			case 'f': case 'F': case 'x': case 'X':
				continue;
			case 'e': case 'E': case 'p': case 'P':
				sawEP = true;
				continue;
			case '+': case '-':
				if ( !sawEP || sawSign) 
					return ;
				sawSign = true;
				continue;
			default: return;
		}
	}
}
/*
 * /f : 换页
 * /v : 垂直制表
 * /t : 水平制表
 */
static inline bool IsBlank(char ch)
{
	return ' ' == ch || '\t' == ch || '\v' == ch || '\f' == ch;
}

void Lexer::Tokenize()
{
	auto p = _text;
	auto lineBegin = p;
	for(; ;){
		while(IsBlank(p[0]) || '\n' == p[0]){
			if('\n' == p[0]){
				if('\r' == p[1]){
					++p;
					lineBegin = p + 1;
				}
				++_line;
			}
			++p;
		}

		if (0 == p[0]) {
			_tokBuf.push_back(NewToken(Token::END));
			return ;
		}

		int tokTag = Token::END;
		switch(p[0]){
		case '-':
				if ('>' == p[1]) {
					tokTag = Token::PTR_OP; ++p;	
				} else if ('-' == p[1]) {
					tokTag = Token::DEC_OP; ++p;	
				} else if ('=' == p[1]) {
					tokTag = Token::SUB_ASSIGN; ++p;
				} else {
					tokTag = Token::SUB;
				}
				++p; break;
		case '+':
				if ('+' == p[1]) {
					tokTag = Token::INC_OP; ++p;	
				} else if ('=' == p[1]) {
					tokTag = Token::ADD_ASSIGN; ++p;
				} else {
					tokTag = Token::ADD;
				}
				++p; break;
		case '<':
				if ('<' == p[1]) {
						if ('=' == p[2]){
							tokTag = Token::LEFT_ASSIGN; ++p; ++p;
						} else {
							tokTag = Token::LEFT_OP; ++p;
						}
				} else if ('=' == p[1]) {
					tokTag = Token::LE_OP; ++p;
				} else if (':' == p[1]) {
					tokTag = '['; ++p;
				} else if ('%' == p[1]) {
					tokTag = '{'; ++p;
				} else {
					tokTag = Token::LESS;
				}
				++p; break;
		case '>':
				if ('>' == p[1]) {
						if ('=' == p[2]){
							tokTag = Token::RIGHT_ASSIGN; ++p; ++p;
						} else {
							tokTag = Token::RIGHT_OP; ++p;
						}
				} else if ('=' == p[1]) {
					tokTag = Token::GE_OP; ++p;
				} else {
					tokTag = Token::GREAT;
				}
				++p; break;
		case '=':
				if ('=' == p[1]) {
					tokTag = Token::EQ_OP; ++p;
				} else {
					tokTag = Token::EQUAL;
				}
				++p; break;
		case '!':
				if ('=' == p[1]) {
					tokTag = Token::NE_OP; ++p;
				} else {
					tokTag = Token::NOT;
				}
				++p; break;
		case '&':
				if ('&' == p[1]) {
					tokTag = Token::AND_OP; ++p;
				} else if ('=' == p[1]) {
					tokTag = Token::AND_ASSIGN; ++p;
				} else {
					tokTag = Token::AND;
				}
				++p; break;
		case '|':
				if ('|' == p[1]) {
					tokTag = Token::OR_OP; ++p;
				} else if ('=' == p[1]) {
					tokTag = Token::OR_ASSIGN; ++p;
				} else {
					tokTag = Token::OR;
				}
				++p; break;
		case '*':
				if ('=' == p[1]) {
					tokTag = Token::MUL_ASSIGN; ++p;
				} else {
					tokTag = Token::MUL;
				}
				++p; break;
		case '/':
				if ('/' == p[1]) {
					while('\n' != p[0])	
							++p;
					tokTag = Token::IGNORE; 
					++_line;
					continue;
				} else if ('*' == p[1]) {
					for (p += 2; !('*' == p[0] && '/' == p[1]); p++){
							if('\n' == p[0]) 
									++_line;
					}
					tokTag = Token::IGNORE; ++p; ++p; 
					continue;
				} else if ('=' == p[1]) {
					tokTag = Token::DIV_ASSIGN; ++p;
				} else {
					tokTag = Token::DIV;
				}
				++p; break;
		case '%':
				if ('=' == p[1]) {
					tokTag = Token::MOD_ASSIGN; ++p;
				} else if ('>' == p[1]) {
					tokTag = '}'; ++p;
				} else if (':' == p[1]) {
					if ('%' == p[2] && ':' == p[3]) {
						tokTag = Token::DSHARP; p += 3;
					} else {
						tokTag = '#'; ++p;
					}
				} else {
					tokTag = Token::MOD;
				}
				++p;
				break;
		case '^':
				if ('=' == p[1]) {
					tokTag = Token::XOR_ASSIGN; ++p;
				} else {
					tokTag = Token::XOR;
				}
				++p; break;
		case '.':
				if ('.' == p[1]) {
					if ('.' == p[2]) {
						tokTag = Token::ELLIPSIS; ++p; ++p;	
					} else {
						// TO DO: error
						Error(_fileName, _line, _column, "illegal identifier '%s'", "..");
					}
				} else if (IsDigit(p[1])) { // for float constant like: '.123'
					goto constant_handler;
				} else {
					tokTag = Token::DOT;
				}
				++p; break;
		// ????
		case 'u': case 'U': case 'L':
				// character constant
				if ('\'' == p[1]) {
					_tokBegin = p; ++p;
					goto char_handler;
				} else if ('"' == p[1]) {
					_tokBegin = p; ++p;
					goto string_handler;
				} else if ('u' == p[0] && '8' == p[1] && '"' == p[2]) {
					_tokBegin = p; ++p; ++p;
					goto string_handler;
				} else {
					goto letter_handler;
				}
				++p; break;
		case '#':
				if ('#' == p[1]) {
					tokTag = Token::DSHARP; ++p;
				} else {
					tokTag = '#';
				}
				++p; break;
		case ':':
				if ('>' == p[1]) {
					tokTag = ']'; ++p;
				} else {
					tokTag = ':';
				}
				++p; break;
		case '(': case ')': case '[': case ']': case '?':
		case ',': case '{': case '}': case '~': case ';':
				tokTag = p[0]; ++p; break;
		case '\'':
				_tokBegin = p;
		char_handler:
				for (++p; '\'' != p[0] && 0 != p[0]; p++) {
					if ('\\' == p[0]) 
						++p;
				}
				_tokEnd = p + 1;
				tokTag = Token::CONSTANT;
				_tokBuf.push_back(NewToken(tokTag, _tokBegin, _tokEnd));
				++p; continue;
		case '"':
				_tokBegin = p;
		string_handler:
				for (++p; '"' != p[0] && 0 != p[0]; p++) {
					if ('\\' == p[0]) 
						++p;
				}
				_tokEnd = p + 1;
				tokTag = Token::STRING_LITERAL;
				_tokBuf.push_back(NewToken(tokTag, _tokBegin, _tokEnd));
				++p; continue;
		default:
			letter_handler:
				if (IsLetter(p[0])) {
					_tokBegin = p;
					while (IsLetter(p[0]) || IsDigit(p[0])) {
						++p;
					}
					_tokEnd = p;

					tokTag = Token::KeyWordTag(_tokBegin, _tokEnd);
					if (!Token::IsKeyWord(tokTag)){
						tokTag = Token::IDENTIFIER;
						_tokBuf.push_back(NewToken(tokTag, _tokBegin, _tokEnd));
					} else 
						_tokBuf.push_back(NewToken(tokTag));
					continue;
				} else if (IsDigit(p[0])) {
				constant_handler:
					_tokBegin = p;
					ReadConstant(p);
					_tokEnd = p;
					tokTag = Token::CONSTANT;
					_tokBuf.push_back(NewToken(tokTag, _tokBegin, _tokEnd));
					continue;
				} else {
					//TODO: set error: invalid character.
					tokTag = Token::INVALID;
					Error(_fileName, _line, _column, "invalid character '%c'", p[0]);
				}
				++p; break;
		}
		_tokBuf.push_back(NewToken(tokTag));
	}
}
bool Lexer::ReadFile(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	if(nullptr == fp){
		Error("open file '%s' failed", fileName);
		return false;
	}
	_fileName = ParseName(fileName);
	long long fileSize = 0LL;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (fileSize > _maxSize) {
		Error("source file '%s' is too big", _fileName);
		return false;
	}
	// 在获取token的过程中需要最多向前看的歩数
	static const int max_predict = 4;
	auto text = new char[fileSize + 1 + max_predict];
	fileSize = fread((void*)text, sizeof(char), fileSize, fp);
	memset(&text[fileSize], 0, 1 + max_predict);
	_tokBuf.reserve(fileSize  / 8);
	_text = text;
	printf("%s\n", _text);
	return true;
}
const char* Lexer::ParseName(const char* path)
{
	const char* name = path;	
	while (0 != *path){
		if ('\\' == *path || '/' == *path)
				name = path + 1;
		++path;
	}
	return name;
}
