#include "test_calc4.h"
Lexer makeLexer(const std::string& text)
{
	Lexer lexer(text);
	return lexer;
}
void test_lexer_integer()
{
	Lexer lexer = makeLexer("234");
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
void test_lexer_sub()
{
	Lexer lexer = makeLexer("-");
	Token token = lexer.get_next_token();
	assert(token.type == MINUS);
	assert(token.value == "-");
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
	Interpreter interpreter(lexer);
	return interpreter;
}
void test_interpreter_expression1()
{
	Interpreter interpreter = makeInterpreter("7 * 4 / 2");
	int res = interpreter.expr();
	assert(res == 14);
}
void test_interpreter_expression2()
{
	Interpreter interpreter = makeInterpreter("7 * 4 / 2 * 3");
	int res = interpreter.expr();
	assert(res == 42);
}
void test_interpreter_expression3()
{
	Interpreter interpreter = makeInterpreter("10 * 4 * 2 * 3 / 8");
	int res = interpreter.expr();
	assert(res == 30);
}
void test()
{
	test_lexer_integer();
	test_lexer_mul();
	test_lexer_div();
	test_lexer_plus();
	test_lexer_sub();
	test_lexer_eof();
	test_lexer_whitespace();
	test_lexer_addition(); 
	test_lexer_subtraction();
	test_interpreter_expression1();
	test_interpreter_expression2();
	test_interpreter_expression3();
	std::cout << "all pass" << std::endl;
}
