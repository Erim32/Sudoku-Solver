######################################################
# makefile du resolveur de sudoku (sudoku solver)
# Auteur: Remi M
# DATE: 9/12/2016
######################################################

CC=gcc
CFLAGS=-Wall -std=c99 -DNDEBUG
OBJ=grille.o inout.o main.o regles.o resolution.o

util:	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o sudokusolver

#dependences
grille.o: grille.c grille.h
regles.o: regles.c regles.c
inout.o: inout.c inout.h
resolution.o: resolution.c resolution.h
main.o: main.c

#phony
clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC)