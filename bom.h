#include <stdio.h>
#include <string.h>

enum { NOBOM, HASBOM, ERROR, SUCCESS };

int checkBOM(const char *filePath);
int removeBOM(const char *filePath);
int addBOM(const char *filePath);
