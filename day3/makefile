prom = calc3
obj = calc3.o interpreter.o token.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc3.o: calc3.cpp 
	g++ -c calc3.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
token.o: token.cpp
	g++ -c token.cpp

clean:
	rm -rf $(obj) $(prom)
