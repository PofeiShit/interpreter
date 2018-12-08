prom = calc2
obj = calc2.o interpreter.o token.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc2.o: calc2.cpp 
	g++ -c calc2.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
token.o: token.cpp
	g++ -c token.cpp

clean:
	rm -rf $(obj) $(prom)
