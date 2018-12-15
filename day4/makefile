prom = calc4
obj = calc4.o interpreter.o token.o lexer.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc4.o: calc4.cpp 
	g++ -c calc4.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
token.o: token.cpp
	g++ -c token.cpp
lexer.o: lexer.cpp
	g++ -c lexer.cpp

clean:
	rm -rf $(obj) $(prom)
