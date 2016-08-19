CC = clang

CFLAGS = -x c++ -c -std=c++11 -pedantic -Wall
LFLAGS = -lstdc++ -lm

SOURCES = construction.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = construction


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
		$(CC) $(LFLAGS) $(OBJECTS) -o $@

.cpp.o:
		$(CC) $(CFLAGS) $< -o $@

clean:
		rm -f $(EXECUTABLE) $(OBJECTS)

# TARGET = cpp11_test
#$(TARGET): $(TARGET).cpp
#		$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).cpp $(LFLAGS)

