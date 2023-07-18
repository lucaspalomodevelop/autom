CC = g++
CFLAGS = -std=c++17 -Wall -static -static-libgcc -static-libstdc++
SRCDIR = ./src
BINDIR = ./bin

$(BINDIR)/autom: $(SRCDIR)/main.cpp $(SRCDIR)/command.cpp $(SRCDIR)/inputparser.cpp $(SRCDIR)/settings.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(BINDIR)/autom
