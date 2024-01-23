CC=gcc
CFlags=-Wall -Wextra -pedantic -std=c99 -g
LFlags=-lm -lraylib -lglfw 

# Path: src/
SRC=src/
CFiles=$(wildcard $(SRC)*.c)
OFiles=$(CFiles:.c=.o)

spaceinvaders: $(OFiles)
	$(CC) $(CFlags) -o spaceinvaders $^ $(LFlags)

wasm: $(CFiles)
	emcc $(CFiles) -Os -o ./build/index.html $(CFLAGS) 	raylib/libraylib.a \
		-I. -I /usr/local/include \
		-s USE_GLFW=3 \
		-s ASYNCIFY \
		--shell-file shell.html \
		--preload-file assets\
		-s TOTAL_STACK=64MB \
		-s INITIAL_MEMORY=128MB \
		-s ASSERTIONS \
		-DPLATFORM_WEB \
		-Wlimited-postlink-optimizations \
		-s GL_ENABLE_GET_PROC_ADDRESS=1


%.o: %.c
	$(CC) $(CFlags) -c -o $@ $< 

clean:
	rm -f $(SRC)*.o spaceinvaders
	rm -f build/spaceinvaders.js build/spaceinvaders.wasm build/spaceinvaders.html build/spaceinvaders.data

