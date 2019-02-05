prom = calc13
obj = calc13.o token.o lexer.o ast.o parser.o interpreter.o symbol.o semantic.o symbol01.o symbol02.o  symbol04.o symbol05.o symbol06.o


$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc13.o: calc13.cpp 
	g++ -c -std=c++11 calc13.cpp
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
	g++ -c -std=c++11 symbol.cpp
semantic.o: semantic.cpp
	g++ -c -std=c++11 semantic.cpp
symbol01.o: symbol01.cpp
	g++ -c -std=c++11 symbol01.cpp
symbol02.o: symbol02.cpp
	g++ -c -std=c++11 symbol02.cpp
symbol04.o: symbol04.cpp
	g++ -c -std=c++11 symbol04.cpp
symbol05.o: symbol05.cpp
	g++ -c -std=c++11 symbol05.cpp
symbol06.o: symbol06.cpp
	g++ -c -std=c++11 symbol06.cpp
clean:
	rm -rf $(obj) $(prom)
