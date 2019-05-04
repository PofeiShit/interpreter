#include "lexer.h"
/*
 * /f : 换页
 * /v : 垂直制表
 * /t : 水平制表
 */
static inline bool IsBlank(char ch)
{
	return ' ' == ch || '\t' == ch || '\v' == ch || '\f' == ch;
}
void Tokenize()
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
				/*} else if (':' == p[1]) {
					tokTag = '['; ++p;
				} else if ('%' == p[1]) {
					tokTag = '{'; ++p;
					*/
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
		}
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
	static const int max_predict = 1;
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
