prom = calc6
obj = calc6.o interpreter.o token.o lexer.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc6.o: calc6.cpp 
	g++ -c calc6.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
token.o: token.cpp
	g++ -c token.cpp
lexer.o: lexer.cpp
	g++ -c lexer.cpp

clean:
	rm -rf $(obj) $(prom)
