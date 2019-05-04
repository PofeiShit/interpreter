#ifndef _LEXER_H_
#define _LEXER_H_
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

				void Tokenize(void);
		private:
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
};
#endif
