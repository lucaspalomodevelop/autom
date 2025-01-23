CC = g++
CFLAGS = -std=c++17 -Wall -static -static-libgcc -static-libstdc++
SRCDIR = ./src
BINDIR = ./bin



.PHONY: clean generate build

all: generate build

generate:
	mkdir -p $(BINDIR)

clean:
	rm -f $(BINDIR)/autom

build: $(BINDIR)/autom

$(BINDIR)/autom: $(SRCDIR)/main.cpp $(SRCDIR)/command.cpp $(SRCDIR)/inputparser.cpp $(SRCDIR)/settings.cpp
	$(CC) $(CFLAGS) $^ -o $@

install: 
	cp $(BINDIR)/autom /usr/local/bin/autom