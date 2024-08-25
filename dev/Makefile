CXX = g++
CXXFLAGS = -Wall -std=c++11 -lX11
SRC = main.cpp
OBJ = main
all: $(OBJ)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OBJ)	

run: all
	sudo ./$(OBJ)

clean:
	rm -rf $(OBJ) 
