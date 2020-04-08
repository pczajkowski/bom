#include <stdio.h>
#include <string.h>

enum { NOBOM, HASBOM, SUCCESS, ERROROPENINPUT, ERROROPENTEMP, ERRORINPUT, ERROROUTPUT, ERRORREMOVE, ERRORRENAME, ERRORCLOSEINPUT, ERRORCLOSETEMP, ERRORSEEK, ERRORWRITINGTEMP};

int checkBOM(const char *filePath);
int removeBOM(const char *filePath);
int addBOM(const char *filePath);
