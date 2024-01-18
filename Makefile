CC=gcc
CFlags=-Wall -Wextra -pedantic -std=c99 -g
LFlags=-lm -lraylib -lglfw 

# Path: src/
SRC=src/
CFiles=$(wildcard $(SRC)*.c)
 
spaceinvaders: $(CFiles)
	$(CC) $(CFlags) -o spaceinvaders $(CFiles)  $(LFlags)
