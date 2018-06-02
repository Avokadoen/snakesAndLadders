CC=g++
CFLAGS=-c -Wall -std=c++17
LDFLAGS=
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp board.cpp tile.cpp player.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main
BINDIR=~/sourcecpp/mathprog/snakesLadders/

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE)

install:
	#install -s $(EXECUTABLE) $(BINDIR)
	sudo cp -u $(EXECUTABLE) $(BINDIR)
uninstall:
	sudo rm $(BINDIR)/$(EXECUTABLE)
