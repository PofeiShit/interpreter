cc = g++
prom = calc5
obj = calc5.o lexer.o interpreter.o token.o test_calc5.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)
%.o: %.c
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
