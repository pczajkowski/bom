#include "bom.h"

void usage(char *executable) {
	printf("Usage:\n%s <filePath> c - to check for BOM.\n", executable);
	printf("%s <filePath> r - to remove BOM.\n", executable);
	printf("%s <filePath> a - to add BOM.\n", executable);
}

void reportError(int errorType) {
	switch(errorType) {
		case ERROROPENINPUT:
			puts("Error opening input file!");
			break;
		case ERROROPENTEMP:
			puts("Error opening temp file!");
			break;
		case ERRORINPUT:
			puts("Error reading input file!");
			break;
		case ERROROUTPUT:
			puts("Error writing temp file!");
			break;
		case ERRORREMOVE:
			puts("Error removing input file!");
			break;
		case ERRORRENAME:
			puts("Error renaming temp file!");
			break;
		case ERRORCLOSEINPUT:
			puts("Error closing input file!");
			break;
		case ERRORCLOSETEMP:
			puts("Error closing temp file!");
			break;
		case ERRORSEEK:
			puts("Error seeking input file!");
			break;
		default:
			printf("Unrecognized error: %d\n", errorType);
	}
}

int main(int argc, char **argv) {
	if (argc < 3) {
		usage(argv[0]);
		return 1;
	} 

	char *inputFileName = argv[1];

	if (strcmp(argv[2], "c") == 0) {
		int result = checkBOM(inputFileName);
		result == HASBOM ? printf("%s has BOM.\n", inputFileName) :
			result == NOBOM ? printf("%s has no BOM.\n", inputFileName) : reportError(result);
	}
	if (strcmp(argv[2], "r") == 0) {
		int result = removeBOM(inputFileName);
		result == SUCCESS ? printf("BOM removed from %s.\n", inputFileName) : reportError(result);
	}
	if (strcmp(argv[2], "a") == 0) {
		int result = addBOM(inputFileName);
		result == SUCCESS ? printf("BOM added to %s.\n", inputFileName) : reportError(result);
	}

	return 0;
}
