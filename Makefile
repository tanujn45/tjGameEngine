CXX = g++
CFLAGS = -Wall -g -std=c++11
LIBS = -lX11 -lpthread -lXext
TARGET = test
SRCS = test.cpp
HDRS = tjGameEngine.h

all: $(TARGET)

$(TARGET): $(SRCS) $(HDRS)
	$(CXX) -o $(TARGET) $(SRCS) $(HDRS) $(LIBS)

run: clean all
	./$(TARGET)

clean:
	rm -f $(TARGET)
