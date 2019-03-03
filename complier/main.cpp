#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;				// current token
char *src, *old_srcc;	// pointer to source code string;
int poolsize;			// default size of text/data/stack
int line;				// line number;
int *text, 				// text segment
	*old_text,			// for dump text segment
	*stack;				// stack
char *data;				// data segment
int *pc, *bp, *sp, ax, cycle;	// virtual machine registers
// instructions
enmu { LEA, IMM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
		OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV, 		MOD, OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT};
void next(){
	token = *src++;
	return ;
}
void expression(int level){
	// do nothing
}
void program(){
	next();			// get next token
	while(token > 0){
		printf("token is: %c\n", token);
		next();
	}
}
int eval() {	// do nothing yet
	int op, *tmp;
	while(1){
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
		else if(op == LEV)	{sp = bp
	}
	return 0;
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
	memset(text, 0, poolsize);
	memset(data, 0, poolsize);
	memset(stack, 0, poolsize);

	bp = sp = (int*)((int)stack + poolsize);
	ax = 0;
	program();
	return eval();
}

