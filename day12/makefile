prom = calc

objs = $(patsubst %.cpp, %.o, $(wildcard *.cpp))
CXXFLAGS = -DUNIT_TEST -std=c++11
$(prom): $(objs)
	g++ -o $(prom) $(objs)
%.o:%.cpp
	g++ -c $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(objs) $(prom)
