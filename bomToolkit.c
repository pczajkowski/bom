#include "bom.h"

void usage(char *executable) {
    printf("Usage: %s <filePath> c - to check for BOM.\n", executable);
    printf("%s <filePath> r - to remove BOM.\n", executable);
    printf("%s <filePath> a - to add BOM.\n", executable);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        usage(argv[0]);
        return 1;
    } 

    char *inputFileName = argv[1];

    if (strcmp(argv[2], "c") == 0) {
        checkBOM(inputFileName) == HASBOM ? printf("%s has BOM.\n", inputFileName) : printf("%s has no BOM.\n", inputFileName);
    }
    if (strcmp(argv[2], "r") == 0) {
        removeBOM(inputFileName) == SUCCESS ? printf("BOM removed from %s.\n", inputFileName) : printf("Error removing BOM from %s!\n", inputFileName);
    }
    if (strcmp(argv[2], "a") == 0) {
        addBOM(inputFileName) == SUCCESS ? printf("BOM added to %s.\n", inputFileName) : printf("Error adding BOM to %s!\n", inputFileName);
    }
   
    return 0;
}