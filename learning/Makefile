CXX = g++
CFLAGS = -Wall -std=c++11 

SRCS = $(wildcard ./*.cpp)
OBJS = $(SRCS:./%.cpp=./%.o)

all: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^

clean 
	rm -rf $(OBJS)
