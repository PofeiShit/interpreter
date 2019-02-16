prom = calc

objs = $(patsubst %.cpp, %.o, $(wildcard *.cpp))

$(prom): $(objs)
	g++ -o $(prom) $(objs)
%.o:%.cpp
	g++ -c $< -o $@

clean:
	rm -rf $(objs) $(prom)
