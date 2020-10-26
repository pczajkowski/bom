#include "bom.h"

void usage(char *executable) {
	printf("Usage:\n%s <filePath> c - to check for BOM.\n", executable);
	printf("%s <filePath> r - to remove BOM.\n", executable);
	printf("%s <filePath> a - to add BOM.\n", executable);
}

void reportError(int errorType) {
	switch(errorType) {
		case ERROROPENINPUT:
			perror("Error opening input file");
			break;
		case ERROROPENTEMP:
			perror("Error opening temp file");
			break;
		case ERRORINPUT:
			perror("Error reading input file");
			break;
		case ERROROUTPUT:
			perror("Error writing temp file");
			break;
		case ERRORREMOVE:
			perror("Error removing input file");
			break;
		case ERRORRENAME:
			perror("Error renaming temp file");
			break;
		case ERRORCLOSEINPUT:
			perror("Error closing input file");
			break;
		case ERRORCLOSETEMP:
			perror("Error closing temp file");
			break;
		case ERRORSEEK:
			perror("Error seeking input file");
			break;
		case ERRORWRITINGTEMP:
			perror("Error writing to temp file");
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
	int result;

	switch(argv[2][0]) {
		case 'c':
			result = checkBOM(inputFileName);
			result == HASBOM ? printf("%s has BOM.\n", inputFileName) :
				result == NOBOM ? printf("%s has no BOM.\n", inputFileName) : reportError(result);
			break;
		case 'r':
			result = removeBOM(inputFileName);
			result == SUCCESS ? printf("BOM removed from %s.\n", inputFileName) : reportError(result);
			break;
		case 'a':
			result = addBOM(inputFileName);
			result == SUCCESS ? printf("BOM added to %s.\n", inputFileName) : reportError(result);
			break;
		default:
			puts("No such option!");
			usage(argv[0]);
			return 1;
	}

	return 0;
}
