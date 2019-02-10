#include "test_calc2.h"
Interpreter makeInterpreter(const std::string& text)
{
	Interpreter interpreter(text);
	return interpreter;
}
void test_lexer_integer()
{
	Interpreter lexer = makeInterpreter("234");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "234");
}
void test_lexer_plus()
{
	Interpreter lexer = makeInterpreter("+");
	Token token = lexer.get_next_token();
	assert(token.type == PLUS);
	assert(token.value == "+");
}
void test_lexer_sub()
{
	Interpreter lexer = makeInterpreter("-");
	Token token = lexer.get_next_token();
	assert(token.type == SUB);
	assert(token.value == "-");
}
void test_lexer_eof()
{
	Interpreter lexer = makeInterpreter("-");
	Token token = lexer.get_next_token();
	token = lexer.get_next_token();
	assert(token.type == EOF_);
}
void test_lexer_whitespace()
{
	Interpreter lexer = makeInterpreter("    23");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "23");
}
void test_lexer_addition()
{
	Interpreter lexer = makeInterpreter("2+3");
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
	Interpreter lexer = makeInterpreter(" 27   -    3 ");
	Token token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "27");

	token = lexer.get_next_token();
	assert(token.type == SUB);
	assert(token.value == "-");

	token = lexer.get_next_token();
	assert(token.type == INTEGER);
	assert(token.value == "3");

	token = lexer.get_next_token();
	assert(token.type == EOF_);
}
void test_interpreter_addition()
{
	Interpreter interpreter = makeInterpreter("  23  + 7");
	int res = interpreter.expr();
	assert(res == 30);
}
void test_interpreter_subtraction()
{
	Interpreter interpreter = makeInterpreter("       27-7   ");
	int res = interpreter.expr();
	assert(res == 20);
}
void test()
{
	test_lexer_integer();
	test_lexer_plus();
	test_lexer_sub();
	test_lexer_eof();
	test_lexer_whitespace();
	test_lexer_addition();
	test_lexer_subtraction();
	test_interpreter_addition();
	test_interpreter_subtraction();
	std::cout << "all pass" << std::endl;
}
