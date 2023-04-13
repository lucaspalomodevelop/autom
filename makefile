CC = g++
CFLAGS = -std=c++11 -Wall
SRCDIR = ./src
BINDIR = ./bin

$(BINDIR)/autom: $(SRCDIR)/main.cpp $(SRCDIR)/command.cpp $(SRCDIR)/inputparser.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(BINDIR)/autom