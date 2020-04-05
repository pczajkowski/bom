CFLAGS=-Wall -Wextra -Wshadow -O3 -std=c99
objects=bom.o

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

default: bomToolkit
