#ifndef TOKEN_H_
#define TOKEN_H_
#include "types.h"
class Token
{
	public:
		std::string type;
		std::string value;
		void show();

		Token(){
			type = "";
			value = "";
		}
		Token(const std::string &_type, const std::string &_value):
			type(_type), value(_value){}
		
};
#endif
