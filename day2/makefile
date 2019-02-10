cc = g++
prom = calc2
obj = calc2.o interpreter.o token.o test_calc2.o

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)
%.o: %.c
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
