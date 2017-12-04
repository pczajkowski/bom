CFLAGS=-g -Wall -Wextra -O3 -std=gnu99
objects=bom.o

test_bom: $(objects)

clean:
	@rm *.o

test: test_bom
	@rm *.o
	@cp testBOM testRemove
	@cp testNoBOM testAdd
	@./test_bom
	@rm test_bom
	@rm testRemove
	@rm testAdd
