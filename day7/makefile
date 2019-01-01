prom = calc7
obj = calc7.o token.o lexer.o ast.o num.o binoperator.o parser.o interpreter.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc7.o: calc7.cpp 
	g++ -c calc7.cpp
token.o: token.cpp
	g++ -c token.cpp
lexer.o: lexer.cpp
	g++ -c lexer.cpp
ast.o: ast.cpp
	g++ -c ast.cpp
num.o: num.cpp
	g++ -c num.cpp
binoperator.o: binoperator.cpp
	g++ -c binoperator.cpp
parser.o: parser.cpp
	g++ -c parser.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
clean:
	rm -rf $(obj) $(prom)
