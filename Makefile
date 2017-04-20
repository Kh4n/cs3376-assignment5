SHELL = /bin/sh
FLAGS = -Wall -g
CC = g++

all:    TwoPipesThreeChildren TwoPipesTwoChildren Dynpipe

TwoPipesThreeChildren:    TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesThreeChildren.cpp

TwoPipesTwoChildren:		TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp	

Dynpipe:		Dynpipe.cpp
	$(CC) $(FLAGS) -o $@ Dynpipe.cpp

clean:
	rm TwoPipesThreeChildren TwoPipesTwoChildren Dynpipe
