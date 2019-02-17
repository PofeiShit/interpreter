prom = calc

objs = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXXFLAGS = -DUNIT_TEST
$(prom): $(objs)
	g++ -o $(prom) $(objs)
%.o:%.cpp
	g++ -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(objs) $(prom)
