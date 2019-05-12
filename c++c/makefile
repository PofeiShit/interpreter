CC := g++

CXXFLAGS := -fpermissive -std=c++11 -Wall 
OBJS := $(patsubst %.cpp, %.o, $(wildcard *.cpp))
TARGET := cxxcomplier

$(TARGET) : $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
%.o:%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@ 	
	
clean:
	rm -rf $(TARGET) $(OBJS)

