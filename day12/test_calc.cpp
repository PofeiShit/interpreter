#include "test_calc.h"
#include <stdexcept>

Lexer makeLexer(const std::string& text)
{
	Lexer lexer(text);
	return lexer;
}
void test_tokens()
{
	const int len = 16;
	std::string text[] = {"234", "3.14", "*", "DIV", "/", "+", "-", "(", ")", ":=", ".", "number", ";", "BEGIN", "END", "PROCEDURE"};
	std::string token_type[] = {INTEGER_CONST, REAL_CONST, MUL, INTEGER_DIV, FLOAT_DIV, PLUS, MINUS, LPAREN, RPAREN, ASSIGN, DOT, ID, SEMI, BEGIN, END, PROCEDURE};
	std::string token_value[] = {"234", "3.14", "*", "DIV", "/", "+", "-", "(", ")", ":=", ".", "NUMBER", ";", "BEGIN", "END", "PROCEDURE"};
	for(int i = 0; i < len; i++){
		Lexer lexer = makeLexer(text[i]);
		Token token = lexer.get_next_token();
		assert(token.type == token_type[i]);
		assert(token.value == token_value[i]);
	}

}

Interpreter makeInterpreter(const std::string& text)
{
	Lexer lexer(text);
	Parser parser(lexer);
	AST* tree = parser.parser();
	SymbolTableBuilder symtab_builder;
	symtab_builder.visit(static_cast<Program*>(tree));

	Interpreter interpreter(tree);
	return interpreter;
}
void test_integer_arithmetic_expression()
{
	const int len = 11;
	std::string expr[] = {"3", "2 + 7 * 4", "7 - 8 / 4", "14 + 2 * 3 - 6 / 2", "7 + 3 * (10 / (12 / (3 + 1) - 1))", "7 + 3 * (10 / (12 / (3 + 1) - 1)) / (2 + 3) - 5 - 3 + (8)", "7 + (((3 + 2)))", "- 3", "+ 3", "5 - - - + - 3", "5 - - - + - (3 + 4) - +2"};
	int result[] = {3, 30, 5, 17, 22, 10, 12, -3, 3, 8, 10};
	for(int i = 0; i < len; i++){
		std::string text = "PROGRAM Test; VAR a : INTEGER; BEGIN a := " + expr[i] + "END.";
		Interpreter interpreter = makeInterpreter(text);
		interpreter.interpret();
		assert(atoi(interpreter.GLOBAL_SCOPE["A"].c_str()) == result[i]);
	}
}
void test_float_arithmetic_expression()
{
	const int len = 3;
	std::string expr[] = {"3.14", "2.14 + 7 * 4", "7.14 - 8 / 4"};
	float result[] = {3.14, 30.14, 5.14};
	for(int i = 0; i < len; i++){
		std::string text = "PROGRAM Test; VAR a : REAL; BEGIN a := " + expr[i] + "END.";
		Interpreter interpreter = makeInterpreter(text);
		interpreter.interpret();
		assert(fabs(atof(interpreter.GLOBAL_SCOPE["A"].c_str()) - result[i]) < 0.001);
	}

}
void test_program()
{
		std::string text = 
				" \
				PROGRAM Part12; \
				VAR \
					number 		: INTEGER; \
					a, b		: INTEGER; \
					y			: REAL; \
					PROCEDURE P1; \
					VAR \
							a : REAL; \
							k : INTEGER; \
							PROCEDURE P2; \
							VAR \
								a, z : INTEGER; \
								BEGIN {P2} \
									z : 777; \
								END; {P2} \
					BEGIN {P1} \
								\
					END{P1}; \
				BEGIN  {Part12} \
						number := 2; \
						a := number; \
						b := 10 * a + 10 * number DIV 4; \
						y := 20 / 7 + 3.14; \
				END. {Part12} \
				";
		Interpreter interpreter = makeInterpreter(text);
		interpreter.interpret();

		assert(interpreter.GLOBAL_SCOPE.size() == 4);
		assert(atoi(interpreter.GLOBAL_SCOPE["NUMBER"].c_str()) == 2);
		assert(atoi(interpreter.GLOBAL_SCOPE["A"].c_str()) == 2);
		assert(atoi(interpreter.GLOBAL_SCOPE["B"].c_str()) == 25);
		assert(fabs(atof(interpreter.GLOBAL_SCOPE["Y"].c_str()) - ((float)20 / (float)7 + 3.14)) < 0.001);
}
void test_expression_invalid_syntax()
{
	Interpreter interpreter = makeInterpreter("BEGIN a := 10 *; END.");
	try{
		interpreter.interpret();
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
		test_tokens();
	std::cout << "lexer all pass\n";
	test_integer_arithmetic_expression();
	test_float_arithmetic_expression();
	test_program();
	std::cout << "interpreter all pass\n";

	test_expression_invalid_syntax();
	test_expression_invalid_syntax2();
	std::cout << "all pass" << std::endl;
}
