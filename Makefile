CXX = g++

CXXFLAGS = -Wall -Werror -Wextra -I include

SRCS = src/Bot.cpp src/Rooms.cpp src/Strategy.cpp src/Vertex.cpp

OBJS = $(SRCS:src/%.cpp=bin/%.o)

TARGET = bin/main

all: $(TARGET)

bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
