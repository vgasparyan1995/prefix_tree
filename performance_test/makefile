EXECUTABLE = ptest
SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
INCLUDEPATH = ../include
CC = g++
CPPFLAGS = -std=c++14 -O2 -Wall -c -I$(INCLUDEPATH)

.PHONY : all clean

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

.cpp.o:
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
