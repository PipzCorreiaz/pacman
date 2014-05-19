CC=g++
CFLAGS= -lGL -lglut -lGLU -g -std=c++11 -pthread
PROGRAM=pacman
PROGSRCDIR=PacmanParty
PROGSRC=$(wildcard $(PROGSRCDIR)/*.cpp)

all: pacman

pacman: $(PROGSRC)
	$(CC) $(PROGSRC) $(CFLAGS) -o $(PROGRAM)

clean:
	rm -rf $(PROGRAM)
