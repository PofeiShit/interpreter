prom = calc11
obj = calc11.o token.o lexer.o ast.o parser.o interpreter.o symbol.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc11.o: calc11.cpp 
	g++ -c -std=c++11 calc11.cpp
token.o: token.cpp
	g++ -c token.cpp
lexer.o: lexer.cpp
	g++ -c lexer.cpp
ast.o: ast.cpp
	g++ -c ast.cpp
parser.o: parser.cpp
	g++ -c parser.cpp
interpreter.o: interpreter.cpp
	g++ -c -std=c++11 interpreter.cpp
symbol.o: symbol.cpp
	g++ -c symbol.cpp
clean:
	rm -rf $(obj) $(prom)
