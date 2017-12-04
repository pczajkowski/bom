#include <assert.h>
#include <stdio.h>
#include "bom.h"

char *fileWithBOM = "./testBOM";
char *fileWithoutBOM = "./testNoBOM";

void testCheckBOM(void) {
	assert(HASBOM == checkBOM(fileWithBOM));
	assert(NOBOM == checkBOM(fileWithoutBOM));
}

char *fileBOMRemoval = "./testRemove";

void testRemoveBOM(void) {
    int result = removeBOM(fileBOMRemoval);
	assert(ERROR != result);
    assert(SUCCESS == result);
    assert(NOBOM == checkBOM(fileBOMRemoval));
}

char *fileBOMAddition = "./testAdd";

void testAddBOM(void) {
    int result = addBOM(fileBOMAddition);
    assert(ERROR != result);
    assert(SUCCESS == result);
    assert(HASBOM == checkBOM(fileBOMAddition));
}

int main(int argc, char **argv) {
	(void)argc;
	(void)argv;
	testCheckBOM();
	testRemoveBOM();
    testAddBOM();
	printf("OK\n");
}
