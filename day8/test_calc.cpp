#include "test_calc.h"
#include <stdexcept>
Lexer makeLexer(const std::string& text)
{
	Lexer lexer(text);
	return lexer;
}
void test_lexer_integer()
{ Lexer lexer = makeLexer("234");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "234");
}
void test_lexer_mul()
{
	Lexer lexer = makeLexer("*"); Token token = lexer.get_next_token();
	assert(token.type == MUL);
	assert(token.value == "*");
}
void test_lexer_div()
{
	Lexer lexer = makeLexer("/");
	Token token = lexer.get_next_token();
	assert(token.type == DIV);
	assert(token.value == "/");
}
void test_lexer_plus()
{
	Lexer lexer = makeLexer("+");
	Token token = lexer.get_next_token();
	assert(token.type == PLUS);
	assert(token.value == "+");
}
void test_lexer_minus()
{
	Lexer lexer = makeLexer("-");
	Token token = lexer.get_next_token();
	assert(token.type == MINUS);
	assert(token.value == "-");
}
void test_lexer_lparen()
{
	Lexer lexer = makeLexer("(");
	Token token = lexer.get_next_token();
	assert(token.type == LPAREN);
	assert(token.value == "(");
}
void test_lexer_rparen()
{
	Lexer lexer = makeLexer(")");
	Token token = lexer.get_next_token();
	assert(token.type == RPAREN);
	assert(token.value == ")");
}
void test_lexer_eof()
{
	Lexer lexer = makeLexer("-");
	Token token = lexer.get_next_token();
	token = lexer.get_next_token();
	assert(token.type == EOF_);
}
void test_lexer_whitespace()
{
	Lexer lexer = makeLexer("    23");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "23");
}
void test_lexer_addition()
{
	Lexer lexer = makeLexer("2+3");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "2");

	token = lexer.get_next_token();
	assert(token.type == PLUS);
	assert(token.value == "+");

	token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "3");

	token = lexer.get_next_token();
	assert(token.type == EOF_);
}
void test_lexer_subtraction()
{
	Lexer lexer = makeLexer(" 27   -    3 ");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "27");

	token = lexer.get_next_token();
	assert(token.type == MINUS);
	assert(token.value == "-");

	token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "3");

	token = lexer.get_next_token();
	assert(token.type == EOF_);
}
Interpreter makeInterpreter(const std::string& text)
{
	Lexer lexer(text);
	Parser parser(lexer);
	Interpreter interpreter(parser);
	return interpreter;
}
void test_interpreter_expression1()
{
	Interpreter interpreter = makeInterpreter("3");
	int res = interpreter.interpret();
	assert(res == 3);
}
void test_interpreter_expression2()
{
	Interpreter interpreter = makeInterpreter("2 + 7 * 4");
	int res = interpreter.interpret();
	assert(res == 30);
}
void test_interpreter_expression3()
{
	Interpreter interpreter = makeInterpreter("7 - 8 / 4");
	int res = interpreter.interpret();
	assert(res == 5);
}
void test_interpreter_expression4()
{
	Interpreter interpreter = makeInterpreter("14 + 2 * 3 - 6 / 2");
	int res = interpreter.interpret();
	assert(res == 17);
}
void test_interpreter_expression5()
{
	Interpreter interpreter = makeInterpreter("7 + 3 * (10 / (12 / (3 + 1) - 1))");
	int res = interpreter.interpret();
	assert(res == 22);
}
void test_interpreter_expression6()
{
	Interpreter interpreter = makeInterpreter("7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)");
	int res = interpreter.interpret();
	assert(res == 10);
}
void test_interpreter_expression7()
{
	Interpreter interpreter = makeInterpreter("7 + (((3 + 2)))");
	int res = interpreter.interpret();
	assert(res == 12);
} void test_interpreter_expression8()
{
	Interpreter interpreter = makeInterpreter("- 3");
	int res = interpreter.interpret();
	assert(res == -3);
}

void test_interpreter_expression9()
{
	Interpreter interpreter = makeInterpreter("+ 3");
	int res = interpreter.interpret();
	assert(res == 3);
}
void test_interpreter_expression10()
{
	Interpreter interpreter = makeInterpreter("5 - - - + - 3");
	int res = interpreter.interpret();
	assert(res == 8);
}
void test_interpreter_expression11()
{
	Interpreter interpreter = makeInterpreter("5 - - - + - (3 + 4) - +2");
	int res = interpreter.interpret();
	assert(res == 10);
}
void test_no_expression()
{
	Interpreter interpreter = makeInterpreter("        ");
	try{
		int res = interpreter.interpret();
	}
	catch(std::exception e){
			std::cout << "no expression\n";
	}
}
void test_expression_invalid_syntax()
{
	Interpreter interpreter = makeInterpreter("10 *");
	try{
		int res = interpreter.interpret();
	}
	catch(std::exception e){
			std::cout << "invalid syntax\n";
	}
}
void test_expression_invalid_syntax2()
{
	Interpreter interpreter = makeInterpreter("1 (1 + 2)");
	int res = interpreter.interpret();
	if(res == 1)
			std::cout << "invalid syntax2\n";
}
void test()
{
		std::cout << "begin test\n";
	test_lexer_integer();
	test_lexer_mul();
	test_lexer_div();
	test_lexer_plus();
	test_lexer_minus();
	test_lexer_eof();
	test_lexer_whitespace();
	test_lexer_addition(); 
	test_lexer_subtraction();
	std::cout << "lexer all pass\n";
	test_interpreter_expression1();
	test_interpreter_expression2();
	test_interpreter_expression3();
	test_interpreter_expression4();
	test_interpreter_expression5();
	test_interpreter_expression6();
	test_interpreter_expression7();
	test_interpreter_expression8();
	test_interpreter_expression9();
	test_interpreter_expression10();
	test_interpreter_expression11();
	test_no_expression();
	std::cout << "interpreter all pass\n";
	test_expression_invalid_syntax();
	test_expression_invalid_syntax2();
	std::cout << "all pass" << std::endl;
}
