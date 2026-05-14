CXX = g++

CXXFLAGS = -I include

SRCS = src/Vertex.cpp src/Rooms.cpp src/Bot.cpp src/Loger.cpp src/FileLoger.cpp src/FileGraphParser.cpp src/Strategy.cpp main.cpp

OBJS = $(SRCS:src/%.cpp=bin/%.o)

TARGET = bin/main

all: $(TARGET)

bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
