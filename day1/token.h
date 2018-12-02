#ifndef TOKEN_H_
#define TOKEN_H_

#include "types.h"
class Token
{
	public:
		std::string type;
		char value;
		void show();

		Token(){
			type = "";
			value = '\0';
		}
		Token(const std::string &_type, const char& _value):
			type(_type), value(_value){}
		
};
#endif
