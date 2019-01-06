prom = calc8
obj = calc8.o token.o lexer.o ast.o parser.o interpreter.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc8.o: calc8.cpp 
	g++ -c calc8.cpp
token.o: token.cpp
	g++ -c token.cpp
lexer.o: lexer.cpp
	g++ -c lexer.cpp
ast.o: ast.cpp
	g++ -c ast.cpp
parser.o: parser.cpp
	g++ -c parser.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
clean:
	rm -rf $(obj) $(prom)
