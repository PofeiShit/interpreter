cc = g++
prom = calc4
obj = calc4.o lexer.o interpreter.o token.o test_calc4.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)
%.o: %.c
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
