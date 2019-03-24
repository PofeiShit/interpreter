#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
int token;				// current token
char *src, *old_src;	// pointer to source code string;
int poolsize;			// default size of text/data/stack
int line;				// line number;
int *text, 				// text segment
	*old_text,			// for dump text segment
	*stack;				// stack
char *data;				// data segment
int *pc, *bp, *sp, ax, cycle;	// virtual machine registers
int token_val;			// value of current token (mainly for number)
int *current_id,		// current parsed ID
	*symbols;			// symbol table
int *idmain;			// the main function
int basetype;			// the type of declaration, make it global for convenience
int expr_type;			// the type of expression
int index_of_bp;
// instructions
enum { LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
		OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, 		MOD, OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT};
// ascii 总共127个
enum {
	Num = 128, Fun, Sys, Glo, Loc, Id, Char, Else, Enum, If, Int, Return, Sizeof, While, Assign, Cond, Lor, Lan, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak
};	
enum {CHAR, INT, PTR};
enum {Token, Hash, Name, Type, Class, Value, BType, BClass, BValue, IdSize};

void next(){
	char *last_pos;
	int hash;
	while (token = *src) {
			++src;
			// parse token here
			if (token == '\n') {
				++line;	
			}
			else if (token == '#') {
				while (*src != 0 && src != '\n') {
						src++;
				}
			}
			else if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token == '_')) {
				// parse identifier
				last_pos = src - 1;
				hash = token;
				while ((*src >= 'a' && *src <= 'z') || (*src >= 'A' && *src <= 'Z') || (*src >= '0' && *src <= '9') || (*src == '_')) {
					hash = hash * 147 + *src; // 147?
					src++;
				}
				// look for existing identifier, linear search
				current_id = symbols;
				while (current_id[Token]) {
					if (current_id[Hash] == hash && !memcmp((char*)current_id[Name], last_pos, src - last_pos)) {
						// found one, return
						token = current_id[Token];
						return ;
					}
					current_id = current_id + IdSize;
				}
				// store new ID
				current_id[Name] = (int)last_pos;
				current_id[Hash] = hash;
				token = current_id[Token] = Id;
				return ;
			}
			else if (token >= '0' && token <= '9') {
				// parse number, three kinds: dec(123) hex(0x123) oct(017)
				token_val = token - '0';
				if (token_val > 0) {
					// dec, start with [1-9]
					while (*src >= '0' && *src <= '9') { 
							token_val = token_val * 10 + *src++ - '0';
					}
				}
				else {
					// starts with number 0
					if (*src == 'x' || *src == 'X') {
							// hex
							token = *++src;
							while ((token >= '0' && token <= '9') || (token >= 'a' && token <= 'f') || (token >= 'A' && token <= 'F')) {
								token_val = token_val * 16 + (token & 15) + (token >= 'A' ? 9 : 0);
								token = *++src;
							}
					} else {
						// oct
						while (*src >= '0' && *src <= '7') {
							token_val = token_val * 8 + *src++ - '0';
						}
					}
				}
				token = Num;
				return ;
			}
			else if (token == '"' || token == '\''){
				// parse string literal, currently, the only supported escape
				// character is \n', store the string literal into data
				last_pos = data;
				while (*src != 0 && *src != token) {
					token_val = *src++;
					if (token_val == '\\') {
						// escape character
						token_val = *src++;
						if (token_val == 'n') {
							token_val = '\n';
						}
					}
					if (token == '"') {
						*data++ = token_val;
					}
				}
				src++;
				// if it is a single character, return Num token
				if (token == '"') {
					token_val = (int)last_pos;
				} else {
					token = Num;
				}
				return ;
			}
			else if (token == '/') {
				if (*src == '/') {
					// skip comment
					while (*src != 0 && *src != '\n') {
						++src;
					}
				} else {
					// divide operator
					token = Div;
					return ;
				}
			}
			else if (token == '=') {
				// parse '== ' and '='
				if (*src == '=') {
					src++;
					token = Eq;
				} else {
					token = Assign;
				}
				return ;
			}
			else if (token == '+') {
				// parse '+' and '++'
				if (*src == '+') {
					src++;
					token = Inc;
				} else {
					token = Add;
				}
				return ;
			}
			else if (token == '-') {
				// parse '-' and '--'
				if (*src == '-') {
					src++;
					token = Dec;
				} else {
					token = Sub;
				}
				return ;
			}
			else if (token == '!') {
				// parse '!=' 
				if (*src == '=') {
					src++;
					token = Ne;
				}
				return ;
			}
			else if (token == '<') {
				// parse '<=', '<<' or '<'
				if (*src == '=') {
					src++;	
					token = Le;
				} else if (*src == '<') {
					src++;
					token = Shl;
				} else {
					token = Lt;
				}
				return ;
			}
			else if (token == '>') {
				// parse '>=', '>>' or '>'
				if (*src == '=') {
					src++;	
					token = Ge;
				} else if (*src == '>') {
					src++;
					token = Shr;
				} else {
					token = Gt;
				}
				return ;
			}
			else if (token == '|') {
				// parse '|' or '||'
				if (*src == '|') {
					src++;
					token = Lor;
				} else {
					token = Or;
				}
				return ;
			}
			else if (token == '&') {
				// parse '&' or '&&'
				if (*src == '&') {
					src++;
					token = Lan;
				} else {
					token = And;
				}
				return ;
			}
			else if (token == '^') {
				token = Xor;
				return ;
			}
			else if (token == '%') {
				token = Mod;
				return ;
			}
			else if (token == '*') {
				token = Mul;
				return ;
			}
			else if (token == '[') {
				token = Brak;
				return ;
			}
			else if (token == '?') {
				token = Cond;
				return ;
			}
			else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':')
			{
				// directly return the character as token;
				return ;
			}
	}
	return ;
}
void match(int tk) {
	if (token == tk) {
		next();	
	}
	else {
		printf("%d: expected token: %d(%c)\n", line, tk, tk);
		exit(-1);
	}
}
void expression(int level){
	int tmp, *id, *addr;
	if (token == Num) {
		match(Num);

		// emit code
		*++text = IMM;
		*++text = token_val;
		expr_type = INT;

	} else if (token == '"') {
		// emit code
		*++text = IMM;
		*++text = token_val;
		match('"');
		// store the rest strings
		while (token == '"') {
			match('"');
		}

		// append the end of string character '\0', all the data are default
		// to 0, so just move data one position forward
		data = (char *)(((int)data + sizeof(int)) & (-sizeof(int)));
		expr_type = PTR;

	} else if (token == Sizeof) {
		// sizeof is actually an unnary operator
		// now only 'sizeof(int)', 'sizeof(char)' and 'sizeof(*...)' are
		// supported.
		match(Sizeof);
		match('(');
		expr_type = INT;

		if (token == Int) {
			match(Int);
		} else if (token == Char) {
			match(Char);
			expr_type = CHAR;
		}

		while (token == Mul) {
			match(Mul);
			expr_type = expr_type + PTR;
		}

		match(')');

		// emit code
		*++text = IMM;
		*++text = (expr_type == CHAR) ? sizeof(char) : sizeof(int);

		expr_type = INT;
	} else if (token == Id) {
		// there are several type when occurs to Id
		// but this is unit, so it can only be 
		// 1. function call
		// 2. Enum variable
		// 3. global/local variable
		match(Id);

		id = current_id;

		if (token == '(') {
			// function call
			match('(');

			// pass in arguments
			tmp = 0; // number of arguments
			while (token != ')') {
				expression(Assign);
				*++text = PUSH;
				tmp++;

				if (token == ',') {
					match(',');
				}
			}
			match(')');
			
			// emit code
			if (id[Class] == Sys) {
				// system functions
				*++text = id[Value];
			}	
			else if (id[Class] == Fun) {
				// function call 
				*++text = CALL;
				*++text = id[Value];
			}
			else {
				printf("%d: bad function call\n", line);
				exit(-1);
			}

			// clean the stack for arguments
			if (tmp > 0) {
				*++text = ADJ;
				*++text = tmp;
			}
			expr_type = id[Type];
		}
		else if (id[Class] == Num) {
			// enum variable
			*++text = IMM;
			*++text = id[Value];
			expr_type = INT;
		}
		else {
			// variable
			if (id[Class] == Loc) {
				*++text = LEA; 
				*++text = index_of_bp - id[Value];
			}
			else if (id[Class] == Glo) {
				*++text = IMM;
				*++text = id[Value];
			}
			else {
				printf("%d: undefined variable\n", line);
				exit(-1);
			}
			
			// emit code, default behaviour is to load the value of the 
			// address which is stored in 'ax'
			expr_type = id[Type];
			*++text = (expr_type == Char) ? LC : LI;
		}
	} else if (token == '(') {
		// cast of parenthesis
		match('(');
		if (token == Int || token == Char) {
			tmp = (token == Char) ? CHAR : INT;	// cast type
			match(token);
			while (token == Mul) {
				match(Mul);
				tmp = tmp + PTR;
			}
			match(')');
			expression(Inc); // cast has precedence as Inc(++)

			expr_type = tmp;
		} else {
			// normal parenthesis
			expression(Assign);
			match(')');
		}
	} else if (token == Mul) {
		// deference *<addr>
		match(Mul);
		expression(Inc); // deference has the same precedence as Inc(++)

		if (expr_type >= PTR) {
			expr_type = expr_type - PTR;
		} else {
			printf("%d: bad deference\n", line);
			exit(-1);
		}
		*++text = (expr_type == CHAR) ? LC : LI;
	} else if (token == And) {
		// get the address of
		match(And);
		expression(Inc); // get the address of
		if (*text == LC || *text == LI) {
			text--;
		} else {
			printf("%d: bad address of\n", line);
			exit(-1);
		}
		expr_type = expr_type + PTR;
	} else if (token == '!') {
		// not 
		match('!');
		expression(Inc);

		// emit code use <expr> == 0
		*++text = PUSH;
		*++text = IMM;
		*++text = 0;
		*++text = EQ;

		expr_type = INT;
	} else if (token == '~') {
		// bitwise not
		match('~');
		expression(Inc);

		// emit code, use <expr> XOR -1
		*++text = PUSH;
		*++text = IMM;
		*++text = -1;
		*++text = XOR;

		expr_type = INT;
	} else if (token == Add) {
		// +var, do nothing
		match(Add);
		expression(Inc);
		
		expr_type = INT;
	} else if (token == Sub) {
		// -var
		match(Sub);

		if (token == Num) {
			*++text = IMM;
			*++text = -token_val;
			match(Num);
		} else {
			*++text = IMM;
			*++text = -1;
			*++text = PUSH;
			expression(Inc);
			*++text = Mul;
		}

		expr_type = INT;
	} else if (token == Inc || token == Dec) {
		tmp = token;
		match(token);
		expression(Inc);
		//
		if (*text == LC) {
			*text = PUSH; // to duplicate the address
			*++text = LC;
		} else if (*text == LI) {
			*text = PUSH;
			*++text = LI;
		} else {
			printf("%d: bad lvalue of pre-increment\n", line);
			exit(-1);
		}
		*++text = PUSH;
		*++text = IMM;

		*++text = (expr_type > PTR) ? sizeof(int) : sizeof(char);
		*++text = (tmp == Inc) ? ADD : SUB;
		*++text = (expr_type == CHAR) ? SC : SI;

	} else {
		printf("%d: bad expression\n", line);
		exit(-1);
	}
	while (token >= level) {
		// parse token for binary operator and postfix operator
		tmp = expr_type;
		if (token == Assign) {
			// var = expr;
			match(Assign);
			if (*text == LC || *text == LI) {
				*text = PUSH; // save the lvalue's pointer
			} else {
				printf("%d: bad lvalue in assignment\n", line);
				exit(-1);
			}
			expression(Assign);

			expr_type = tmp;
			*++text = (expr_type == CHAR) ? SC : SI;
		} else if (token == Cond) {
			// expr ?  a : b
			match(Cond);
			*++text = JZ;
			addr = ++text;
			expression(Assign);
			if (token == ':') {
				match(':');
			} else {
				printf("%d: missing colon in conditional\n", line);
				exit(-1);
			}
			*addr = (int)(text + 3);
			*++text = JMP;
			addr = ++text;
			expression(Cond);
			*addr = (int)(text + 1);
		} else if (token == Lor) {
			// logic or
			match(Lor);
			*++text = JNZ;
			addr = ++text;
			expression(Lan);
			*addr = (int)(text + 1);
			expr_type = INT;
		} else if (token == Lan) {
			// logic and
			match(Lan);
			*++text = JZ;
			addr = ++text;
			expression(Or);
			*addr = (int)(text + 1);
			expr_type = INT;
		} else if (token == Xor) {
			// bitwise xor
			match(Xor);
			*++text = PUSH;
			expression(And);
			*++text = XOR;
			expr_type = INT;
		} else if (token == Add) {
			// add
			match(Add);
			*++text = PUSH;
			expression(Mul);

			expr_type = tmp;
			if (expr_type > PTR) {
				// pointer type, and not 'char *'
				*++text = PUSH;
				*++text = IMM;
				*++text = sizeof(int);
				*++text = MUL;
			}
			*++text = ADD;
		} else if (token == Lt) {
			// less than
			match(Lt);
			*++text = PUSH;
			expression(Shl);
			*++text = Lt;
			expr_type = INT;
		} else if (token == Shl) {
			// shift left 
			match(Shl);
			*++text = PUSH;	
			expression(Add);
			*++text = SHL;
			expr_type = INT;
		} else if (token == Gt) {
			// greater than
			match(Gt);
			*++text = PUSH;
			expression(Shl);
			*++text = GT;
			expr_type = INT;
		}
	}
}
void enum_declaration() {
	// parsse enum [id] { a = 1, b = 3, ... }
	int i;
	i = 0;
	while (token != '}') {
		if (token != Id) {
			printf("%d: bad enum identified %d\n", line, token);
			exit(-1);
		}
		next();
		if (token == Assign) {
			// like {a = 10}
			next();
			if (token != Num) {
				printf("%d: bad enum initializer\n", line);
				exit(-1);
			}
			i = token_val;
			next();
		}
		//printf("%d\n", current_id[Hash]);
		current_id[Class] = Num;
		current_id[Type] = INT;
		current_id[Value] = i++;
		
		if (token == ',') {
			next();
		}
	}
}

void function_parameter()
{
	int type;
	int params;
	params = 0;
	while (token != ')') {
		// int name, ...
		type = INT;
		if (token == Int) {
			match(Int);
		} else if (token == Char) {
			type = CHAR;
			match(Char);
		}
		// pointer type
		while (token == Mul) {
			match(Mul);
			type = type + PTR;
		}

		// parameter name
		if (token != Id) {
			printf("%d, %d: bad parameter declaration\n", __LINE__, line);
			exit(-1);
		}
		if (current_id[Class] == Loc) {
			printf("%d,%d: duplicate parameter declaration\n", __LINE__, line);
			exit(-1);
		}
		match(Id);
		// store the local variable
		current_id[BClass] = current_id[Class]; current_id[Class] = Loc;
		current_id[BType] = current_id[Type]; current_id[Type] = type;
		current_id[BValue] = current_id[Value]; current_id[Value] = params++;	// index of current parameter

		if (token == ',') {
			match(',');
		}
	}

	index_of_bp = params + 1;
}
void statement()
{
	int *a, *b;
	if (token == If) {
		match(If);
		match('(');
		expression(Assign);	// parse condition
		match(')');

		*++text = JZ;
		b = ++text;

		statement(); // parse statement
		if (token == Else) { // parse else
			match(Else);

			// emit	code for JMP B
			*b = (int)text + 3;
			*++text = JMP;
			b = ++text;

			statement();
		}

		*b = (int)(text + 1); 
	} else if (token == While) {
		match(While);

		a = text + 1;

		match('(');
		expression(Assign);
		match(')');

		*++text = JZ;
		b = ++text;

		statement();

		*++text = JMP;
		*++text = (int)a;
		*b = (int)(text + 1);
	} else if (token == Return) {
		// return Expression
		match(Return);

		if (token != ';') {
			expression(Assign);
		}
		match(';');

		// emit code for return
		*++text = LEV;
	} else if (token == '{') {
		// { <statement> ... }
		match('{');
		while (token != '}') {
			statement();
		}

		match('}');
	} else if (token == ';') {
		// empty statement
		match(';');
	}
	else {
		// a = b; or function_call();
		expression(Assign);
		match(';');
	}
}
void function_body()
{
	// type func_name (...) {...}
	// 					 -->|	|<--

	// ... {
	// 1. local declarations
	// 2. statements
	// }
	int pos_local;	// position of local variables on the stack
	int type;
	pos_local = index_of_bp;
	// 
	while (token == Int || token == Char) {
		// local variable declaration, just like global ones.
		basetype = (token == Int) ? INT : CHAR;
		match(token);

		while (token != ';') {
			type = basetype;
			while (token == Mul) {
				match(Mul);
				type = type + PTR;
			}

			if (token != Id) {
				// invalid declaration
				printf("%d: bad local declaration\n", line);
				exit(-1);
			}
			if (current_id[Class] == Loc) {
				// identifier exists
				printf("%d: duplicate local declaration\n", line);
				exit(-1);
			}
			match(Id);
			
			current_id[BClass] = current_id[Class]; current_id[Class] = Loc;
			current_id[BType] = current_id[Type]; current_id[Type] = type;
			current_id[BValue] = current_id[Value]; current_id[Value] = ++pos_local;	// index of current parameter

			if (token == ',') {
				match(',');
			}
		}
		match(';');
	}
	// save the stack size for local variables
	*++text = ENT;
	*++text = pos_local - index_of_bp;

	// statements
	while (token != '}') {
		statement();
	}
	// emit code for leaving the sub function
	*++text = LEV;
}
void function_declaration()
{
	// type func_name (...) {...}
	// 				| this part
	match('(');
	function_parameter();
	match(')');
	match('{');
	function_body();
	
	// unwind local variable declarations for all local variables.
	current_id = symbols;
	while (current_id[Token]) {
		if (current_id[Class] == Loc) {
			current_id[Class] = current_id[BClass];
			current_id[Type] = current_id[BType];
			current_id[Value] = current_id[BValue];
		}
		current_id = current_id + IdSize;
	}
}
void global_declaration()
{
	// global_declaration ::= enum_decl | variable_decl | function_decl
	// 
	// enum_decl ::= 'enum' [id] '{' id ['=' 'num'] {',' id ['=' 'num'] '}'
	// 
	// variable_decl ::= type {'*'} id { ',' {'*'} id } ';'
	//
	// function_decl ::= type {'*'} id '(' parameter_decl ')' '{' body_decl '}'
	int type; // tmp, actual type for variable
	int i;	// tmp
	basetype = INT;
	// parse enum, this should be treated alone.
	if (token == Enum) {
		// enum [id] { a = 10, b = 20, ... }
		match(Enum);
		if (token != '{') {
			match(Id); // skip the [id] part
		}
		if (token == '{') {
			// parse the assign part
			match('{');
			enum_declaration();
			match('}');
		}
		match(';');
		return ;
	}
	// parse type information
	if (token == Int) {
		match(Int);
	}
	else if (token == Char) {
		match(Char);
		basetype = CHAR;
	}
	// parse the comma seperated variable declaration.
	while (token != ';' && token != '}') {
		type = basetype;
		// parse point type, note that there may exist 'int ******x;'
		while (token == Mul) {
			match(Mul);
			type = type + PTR;
		}
		if (token != Id) { 
			// invalid declaration
			printf("%d: bad global declaration\n", line);
			exit(-1);
		}
		if (current_id[Class]) {
			// identifier exists
			printf("%d: duplicate global declaration\n", line);
			exit(-1);
		}
		match(Id);
		
		current_id[Type] = type;

		if (token == '(') {
			current_id[Class] = Fun;
			current_id[Value] = (int)(text + 1); // the memory address of function
			function_declaration();
		} else {
			// variable declaration 
			current_id[Class] = Glo;	// global variable
			current_id[Value] = (int)data;	// assign memory address
			data = data + sizeof(int);
		}
		if (token == ',') {
			match(',');
		}
	}
	next();
}
void program(){
	next();			// get next token
	while(token > 0){
			global_declaration();
	}
}
int eval() {	// do nothing yet
	int op, *tmp;
	cycle = 0;
	while(1){
		cycle++;
		op = *pc++;
		printf("%d\n", op);
		if(op == IMM) 		{ax = *pc++;}
		else if(op == LC) 	{ax = *(char *)ax;}
		else if(op == LI)	{ax = *(int *)ax;}
		else if(op == SC)	{ax = *(char *)*sp++ = ax;}
		else if(op == SI)	{*(int *)*sp++ = ax;}
		else if(op == PUSH)	{*--sp = ax;}
		else if(op == JMP)	{pc = (int*)*pc;}	// jump to the address
		else if(op == JZ)	{pc = ax ? pc + 1 : (int*)*pc;}	// jump if ax is zero
		else if(op == JNZ)	{pc = ax ? (int*)*pc : pc + 1;}	// jump if ax is zero
		// 先将下一条指令入栈，然后将pc赋值为子函数的地址
		else if(op == CALL) {*--sp = (int)(pc + 1); pc = (int*)*pc;}
		else if(op == ENT)	{*--sp = (int)bp; bp = sp; sp = sp - *pc++;}
		else if(op == ADJ) 	{sp = sp + *pc++;}
		else if(op == LEV)	{sp = bp; bp = (int*)*sp++; pc = (int*)*sp++;} // restor call frame and PC
		else if(op == LEA)	{ax = (int)(bp + *pc++);}	// load address for arguments;
		else if(op == OR)	ax = *sp++ | ax;
		else if(op == XOR)	ax = *sp++ ^ ax;
		else if(op == AND)	ax = *sp++ & ax;
		else if(op == EQ)	ax = *sp++ == ax;
		else if(op == NE)	ax = *sp++ != ax;
		else if(op == LT) 	ax = *sp++ < ax;
		else if(op == LE)	ax = *sp++ <= ax;
		else if(op == GT)	ax = *sp++ > ax;
		else if(op == GE)	ax = *sp++ >= ax;
		else if(op == SHL)	ax = *sp++ << ax;
		else if(op == SHR) 	ax = *sp++ >> ax;
		else if(op == ADD)	ax = *sp++ + ax;
		else if(op == SUB)	ax = *sp++ - ax;
		else if(op == MUL)	ax = *sp++ * ax;
		else if(op == DIV) 	ax = *sp++ / ax;
		else if(op == MOD) 	ax = *sp++ % ax;
		else if(op == EXIT)	{ printf("exit(%d)", *sp); return *sp;}
		else if(op == OPEN) { ax = open((char *)sp[1], sp[0]);}
		else if(op == CLOS)	{ ax = close(*sp);}
		else if(op == READ)	{ ax = read(sp[2], (char*)sp[1], *sp);}
		else if(op == PTR) { tmp = sp + pc[1]; ax = printf((char*)tmp[-1], tmp[-2], tmp[-3], tmp[-4], tmp[-5], tmp[-6]);}
		else if(op == MALC)	{ ax = (int)malloc(*sp);}
		else if(op == MSET) { ax = (int)memset((char*)sp[2], sp[1], *sp);}
		else if(op == MCMP) { ax = memcmp((char*)sp[2], (char*)sp[1], *sp);}
		else {
				printf("unknow instruction:%d\n", op);
				return -1;
		}
	}
	return 0;
}
void enum_test()
{
	std::string str[] = {"enum test { a = 1, b, c };", "enum test { a, b, c };", "enum {a = 10, b = 20, c};", "enum {a, b, c};"};	
	char c[] = {'a', 'b', 'c'};
	int res[] = {1, 2, 3, 0, 1, 2, 10, 20, 21, 0, 1, 2};
	for (int i = 0; i < 4; i++) {
		src = str[i].c_str();
		program();
		current_id = symbols;
		int tk = -1;

			while (current_id[Token]) {
				if (current_id[Hash] == 97) {
					// found one, return
					tk = current_id[Token];
					break;
				}
				current_id = current_id + IdSize;
			}

			assert(tk == Id);
			assert(current_id[Value] == res[i * 3 + 0]);
			current_id = current_id + IdSize;
			assert(tk == Id);
			assert(current_id[Value] == res[i * 3 + 1]);
			current_id = current_id + IdSize;
			assert(tk == Id);
			assert(current_id[Value] == res[i * 3 + 2]);
	}
	printf("enum test pass!\n");
}
void variable_test()
{
	std::string str[] = {"int a, b, c;", "int ****d, e, f;", "char g, h, i;", "char *****j, k, l;", "char m, n; int o;"};
	int res[] = {1, 1, 1, 9, 1, 1, 0, 0, 0, 10, 0, 0, 0, 0, 1};
	int hash[] = {97, 100, 103, 106, 109};
	for (int i = 0; i < 5; i++) {
		src = str[i].c_str();
		program();
		current_id = symbols;
		int tk = -1;

			while (current_id[Token]) {
				if (current_id[Hash] == hash[i]) {
					// found one, return
					tk = current_id[Token];
					break;
				}
				current_id = current_id + IdSize;
			}

			assert(tk == Id);
			assert(current_id[Type] == res[i * 3 + 0]);
			current_id = current_id + IdSize;
			assert(tk == Id);
			assert(current_id[Type] == res[i * 3 + 1]);
			current_id = current_id + IdSize;
			assert(tk == Id);
			assert(current_id[Type] == res[i * 3 + 2]);
	}
	printf("variable test pass!\n");
}
void function_test()
{
	std::string str[] = {"int func_test(int a, char b, int *c, char *d) { int e, *f; char ******g, h;}"}; 
	src = str[0].c_str();
	program();

	assert(index_of_bp == 5);
	printf("function test pass\n");	
}
void statement_test()
{
	std::string str[] = {" \
			int main()\n \
			{ \n \
				int a, b, c;\n \
				a = 3; \n \
				b = 4; \n \
				c = a + b;\n \
				return 0;\n \
			}\n" \	
		};
	// instruction : ENT 3 LEA -1 PUSH IMM 3 SI LEA -2 PUSH IMM 4 SI LEA -3 PUSH LEA -1 LI PUSH LEA -2 LI ADD SI IMM 0 LEV LEV
	int res[] = { 6, 3, 0, -1, 13, 1, 3, 11, 0, -2, 13, 1, 4, 11, 0, -3, 13, 0, -1, 9, 13, 0, -2, 9, 25, 11, 1, 0, 8, 8 };
	src = str[0].c_str();
	printf("%s\n", src);
	program();
	int n = sizeof(res) / sizeof(res[0]);	
	for(int i = 0; i < n; i++){
		assert(old_text[1 + i] == res[i]);
	}
	printf("statement test all pass\n");
	if (!(pc = (int *)idmain[Value])) {
		printf("%x\n", pc);
		printf("main() not defined!\n");
		return -1;
	}
	bp = sp = stack + poolsize;
	*--sp = EXIT;
	*--sp = PUSH;
	int *tmp = sp;
	*--sp = 0;
	*--sp = (int)tmp;
	*--sp = (int)tmp;
	eval();
	bp = sp = stack + poolsize;
	assert(*(sp - 9) == 7);
	printf("expression test all pass\n");
}
void lexer_test(){
		std::string str[] = {"\n", "aa", "_a", "_z", "_A", "_Z", "__", "123", "0x123", "0X123", "0xcf", "017", "'a'", "\"a string\"", "/", "==", "=", "++", "+", "--", "-", "!=", "<=", "<<", "<", ">", ">>", ">=", "|", "||", "&", "&&", "^", "%", "*", "[", "?", "~", ";", "{", "}", "(", ")", "]", ",", ":"};	
		int res[] = {14356, 14062, 14087, 13030, 14055, 14060};
		int tk[] = {Div, Eq, Assign, Inc, Add, Dec, Sub, Ne, Le, Shl, Lt, Gt, Shr, Ge, Or, Lor, And, Lan, Xor, Mod, Mul, Brak, Cond};
		src = str[0].c_str();
		next();
		assert(line == 2); printf("token \\n test pass\n");
		for (int i = 1; i <= 6; i++) {
			src = str[i].c_str();
			next();
			assert(current_id[Hash] = res[i - 1]); 
		}
		printf("token Id test pass\n");
		for (int i = 7; i <= 12; i++) {
			src = str[i].c_str();
			next(); 
			assert(token == Num);
		}
		printf("token Num test pass\n");
		src = str[13].c_str();
		next(); 
		char *p = (char*)token_val;
		std::string s("");
		for (int i = 0; i < 8; i++){
			s += *p++;
		}
		assert(s == "a string");
		printf("token string test pass\n");
		for (int i = 14; i < 37; i++) {
			src = str[i].c_str();
			next(); 
			assert(token == tk[i - 14]);
		}
		printf("token test pass\n");
}
int main(int argc, char **argv)
{
	int i, fd;

	argc--;
	argv++;

	poolsize = 256 * 1024; // arbitary size
	line = 1;
	if((fd = open(*argv, 0)) < 0){
		printf("could not open(%s)\n", *argv);
		return -1;
	}
	if(!(src = old_src = malloc(poolsize))){
		printf("could not malloc(%d) for source area\n", poolsize);
		return -1;
	}
	// read the source file
	if((i = read(fd, src, poolsize - 1)) <= 0){
		printf("read() returned %d\n", i);
		return -1;
	}
	src[i] = 0;	// add EOF character
	close(fd);
	// allocate memory for virtual machine
	if(!(text = old_text = malloc(poolsize))){
		printf("could not malloc(%d) for text area\n", poolsize);
		return -1;
	}
	if(!(data = malloc(poolsize))){
		printf("could not malloc(%d) for data area\n", poolsize);
		return -1;
	}
	if(!(stack = malloc(poolsize))){
		printf("could not malloc(%d) for stack area\n", poolsize);
		return -1;
	}
	if (!(symbols = malloc(poolsize))) {
		printf("coudl not malloc(%d) for symbol area\n", poolsize);
		return -1;
	}
	memset(text, 0, poolsize);
	memset(data, 0, poolsize);
	memset(stack, 0, poolsize);
	memset(symbols, 0, poolsize);

	bp = sp = stack + poolsize;
	ax = 0;
	src = "char else enum if int return sizeof while "
			"open read close printf malloc memset memcmp exit void main";
	// add keywords to symbol table
	i = Char;
	while (i <= While) {
		next();
		current_id[Token] = i++;
	}
	// add library to symbol table
	i = OPEN;
	while (i <= EXIT) {
		next();
		current_id[Class] = Sys; // 该标识符的类别
		current_id[Type] = INT; // 标识符的类型,如果是变量，是int型、char型还是指针型
		current_id[Value] = i++; // 标识符的值，如标识符是函数，则存放函数的地址
	}
	next(); current_id[Token] = Char;	// handle void type
	next(); idmain = current_id;	// keep track of main
/*
	if (!(pc = (int *)idmain[Value])) {
		printf("main() not defined!\n");
		return -1;
	}
	*/
	//lexer_test();
	//enum_test();
	//variable_test();
	//function_test();
	statement_test();
	//program();
	return 0;//eval();
}

