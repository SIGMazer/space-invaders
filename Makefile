CC=gcc
CFlags=-Wall -Wextra -pedantic -std=c99 -g
LFlags=-lm -lraylib -lglfw 

# Path: src/
SRC=src/
 
spaceinvaders: $(SRC)main.c 
	$(CC) $(CFlags) -o spaceinvaders  $(SRC)main.c $(LFlags)
