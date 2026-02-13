CXX = g++
CXXFLAGS = -Wall -std=c++17

TARGET = out

SRC = main.c lexer.c parser.c expr.c
OBJ = $(SRC:.cpp=.o)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)
