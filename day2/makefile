prom = calc1
obj = calc1.o interpreter.o token.o

$(prom): $(obj)
	g++ -o $(prom) $(obj)
calc1.o: calc1.cpp 
	g++ -c calc1.cpp
interpreter.o: interpreter.cpp
	g++ -c interpreter.cpp
token.o: token.cpp
	g++ -c token.cpp

clean:
	rm -rf $(obj) $(prom)
