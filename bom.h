#include <stdio.h>
#include <string.h>

#define NOBOM 0
#define HASBOM 1
#define ERROR 2
#define SUCCESS 3

int checkBOM(char *filePath);
int removeBOM(char *filePath);
int addBOM(char *filePath);
