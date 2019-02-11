cc = g++
prom = calc3
obj = calc3.o interpreter.o token.o 

$(prom): $(obj)
	$(cc) -o $(prom) $(obj)
%.o: %.c
	$(cc) -c $< -o $@

clean:
	rm -rf $(obj) $(prom)
