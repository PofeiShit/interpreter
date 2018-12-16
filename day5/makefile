prom = calc5
obj = calc5.o interpreter.o token.o lexer.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc5.o: calc5.cpp 
	g++ -c calc5.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
token.o: token.cpp
	g++ -c token.cpp
lexer.o: lexer.cpp
	g++ -c lexer.cpp

clean:
	rm -rf $(obj) $(prom)
