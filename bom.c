#include "bom.h"

#define BOMSIZE 3
#define CHUNKSIZE 1024
unsigned char bom[] = { 0xEF, 0xBB, 0xBF };

int checkBOM(const char *filePath) {
	FILE *inputFile = fopen(filePath, "r");
	if (inputFile == NULL) return ERROROPENINPUT;

	unsigned char check[BOMSIZE];
	if (BOMSIZE != fread(check, BOMSIZE, 1, inputFile)) {
		if (feof(inputFile)) return NOBOM;
		if (ferror(inputFile)) return ERRORINPUT;
	}
	if (fclose(inputFile)) return ERRORCLOSEINPUT;

	if (!memcmp(&bom, check, BOMSIZE)) return HASBOM;
	return NOBOM;
}

char *tempFileName = "tempFile";

int removeBOM(const char *filePath) {
	if (NOBOM == checkBOM(filePath)) return SUCCESS;

	FILE *inputFile = fopen(filePath, "r");
	if (inputFile == NULL) return ERROROPENINPUT;

	if (fseek(inputFile, BOMSIZE, SEEK_SET)) return ERRORSEEK;

	FILE *tempFile = fopen(tempFileName, "w");
	if (tempFile == NULL) return ERROROPENTEMP;

	char buffer[CHUNKSIZE];
	do {
		int read = fread(buffer, 1, CHUNKSIZE, inputFile);
		fwrite(buffer, 1, read, tempFile);
	} while (!feof(inputFile));
	
	if (fclose(tempFile)) return ERRORCLOSETEMP;
	if (fclose(inputFile)) return ERRORCLOSEINPUT;

	if (remove(filePath)) return ERRORREMOVE;
	if (rename(tempFileName, filePath)) return ERRORRENAME;

	return SUCCESS;
}

int addBOM(const char *filePath) {
	if (HASBOM == checkBOM(filePath)) return SUCCESS;

	FILE *inputFile = fopen(filePath, "r");
	if (inputFile == NULL) return ERROROPENINPUT;

	FILE *tempFile = fopen(tempFileName, "w");
	if (tempFile== NULL) return ERROROPENTEMP;

	int written = fwrite(bom, 1, BOMSIZE, tempFile);
	if (written != BOMSIZE) return ERROROUTPUT;

	char buffer[CHUNKSIZE];
	do {
		int read = fread(buffer, 1, CHUNKSIZE, inputFile);
		fwrite(buffer, 1, read, tempFile);
	} while (!feof(inputFile));

	if (fclose(tempFile)) return ERRORCLOSETEMP;
	if (fclose(inputFile)) return ERRORCLOSEINPUT;

	if (remove(filePath)) return ERRORREMOVE;
	if (rename(tempFileName, filePath)) return ERRORRENAME;

	return SUCCESS;
}
