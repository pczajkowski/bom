CFLAGS=-Wall -Wextra -Wshadow -O3 -std=c99
objects=bom.o
mingw=x86_64-w64-mingw32-gcc

bomToolkit: $(objects)

clean:
	@rm *.o

test:
	cc $(CFLAGS) -c bom.c
	cc $(CFLAGS) test_bom.c $(objects) -o test_bom
	@cp testBOM testRemove
	@cp testNoBOM testAdd
	@./test_bom
	@rm test_bom
	@rm testRemove
	@rm testAdd

win/bomToolkit.exe:
	$(mingw) $(CFLAGS) -c bom.c
	$(mingw) $(CFLAGS) bomToolkit.c $(objects) -o $@

win: win/bomToolkit.exe

default: bomToolkit
