CC=gcc
CFlags=-Wall -Wextra -pedantic -std=c99 -g
LFlags=-lm -lraylib -lglfw 

# Path: src/
SRC=src/
CFiles=$(wildcard $(SRC)*.c)
OFiles=$(CFiles:.c=.o)
 
spaceinvaders: $(OFiles)
	$(CC) $(CFlags) -o spaceinvaders $^ $(LFlags)

%.o: %.c
	$(CC) $(CFlags) -c -o $@ $< 

clean:
	rm -f $(SRC)*.o spaceinvaders

