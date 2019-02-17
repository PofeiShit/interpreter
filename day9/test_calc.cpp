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
void test_lexer_new_tokens()
{
	const int len = 6;
	std::string text[] = {":=", ".", "number", ";", "BEGIN", "END"};
	std::string token_type[] = {ASSIGN, DOT, ID, SEMI, BEGIN, END};
	std::string token_value[] = {":=", ".", "NUMBER", ";", "BEGIN", "END"};
	for(int i = 0; i < 6; i++){
		Lexer lexer = makeLexer(text[i]);
		Token token = lexer.get_next_token();
		assert(token.type == token_type[i]);
		assert(token.value == token_value[i]);
	}
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
void test_arithmetic_expression()
{
	const int len = 11;
	std::string expr[] = {"3", "2 + 7 * 4", "7 - 8 / 4", "14 + 2 * 3 - 6 / 2", "7 + 3 * (10 / (12 / (3 + 1) - 1))", "7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)", "7 + (((3 + 2)))", "- 3", "+ 3", "5 - - - + - 3", "5 - - - + - (3 + 4) - +2"};
	int result[] = {3, 30, 5, 17, 22, 10, 12, -3, 3, 8, 10};
	for(int i = 0; i < 11; i++){
		std::string text = "BEGIN a := " + expr[i] + "END.";
		Interpreter interpreter = makeInterpreter(text);
		interpreter.interpret();
		assert(interpreter.GLOBAL_SCOPE["A"] == result[i]);
	}
}
void test_statement()
{
		std::string text = 
				" \
				BEGIN  \
				BEGIN  \
				number := 2; \
				a := number; \
				b := 10 * a + 10 * number / 4; \
				c := a - - b; \
				END; \
				x := 11; \
				END. \
				";
	Interpreter interpreter = makeInterpreter(text);
	interpreter.interpret();
	assert(interpreter.GLOBAL_SCOPE.size() == 5);
	assert(interpreter.GLOBAL_SCOPE["NUMBER"] == 2);
	assert(interpreter.GLOBAL_SCOPE["A"] == 2);
	assert(interpreter.GLOBAL_SCOPE["B"] == 25);
	assert(interpreter.GLOBAL_SCOPE["C"] == 27);
	assert(interpreter.GLOBAL_SCOPE["X"] == 11);
}
void test_expression_invalid_syntax()
{
	Interpreter interpreter = makeInterpreter("BEGIN a := 10 *; END.");
	try{
		int res = interpreter.interpret();
	}
	catch(std::exception e){
			std::cout << "invalid syntax\n";
	}
}
void test_expression_invalid_syntax2()
{
	Interpreter interpreter = makeInterpreter("BEGIN a := 1 (1 + 2); END.");
	interpreter.interpret();
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
	test_lexer_new_tokens();
	std::cout << "lexer all pass\n";
	test_arithmetic_expression();
	std::cout << "interpreter all pass\n";
	test_expression_invalid_syntax();
	test_expression_invalid_syntax2();
	std::cout << "all pass" << std::endl;
}
