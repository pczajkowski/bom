#include "bom.h"

#define BOMSIZE 3
#define CHUNKSIZE 1024
unsigned char bom[] = { 0xEF, 0xBB, 0xBF };

int checkBOM(const char *filePath) {
	FILE *inputFile = fopen(filePath, "r");
	if (inputFile == NULL) return ERROR;

	unsigned char check[BOMSIZE];
	if (BOMSIZE != fread(check, BOMSIZE, 1, inputFile)) {
		if (feof(inputFile)) return NOBOM;
		if (ferror(inputFile)) return ERROR;
	}
	if (fclose(inputFile)) return ERROR;

	if (!memcmp(&bom, check, BOMSIZE)) return HASBOM;
	return NOBOM;
}

char *tempFileName = "tempFile";

int removeBOM(const char *filePath) {
	if (NOBOM == checkBOM(filePath)) return SUCCESS;

	FILE *inputFile = fopen(filePath, "r");
	if (inputFile == NULL) return ERROR;

	if (fseek(inputFile, BOMSIZE, SEEK_SET)) return ERROR;

	FILE *tempFile = fopen(tempFileName, "w");
	if (tempFile == NULL) return ERROR;

	char buffer[CHUNKSIZE];
	do {
		int read = fread(buffer, 1, CHUNKSIZE, inputFile);
		fwrite(buffer, 1, read, tempFile);
	} while (!feof(inputFile));
	
	if (fclose(tempFile)) return ERROR;
	if (fclose(inputFile)) return ERROR;

	if (remove(filePath)) return ERROR;
	if (rename(tempFileName, filePath)) return ERROR;

	return SUCCESS;
}

int addBOM(const char *filePath) {
	if (HASBOM == checkBOM(filePath)) return SUCCESS;

	FILE *inputFile = fopen(filePath, "r");
	if (inputFile == NULL) return ERROR;

	FILE *tempFile = fopen(tempFileName, "w");
	if (tempFile== NULL) return ERROR;

	for (int i = 0; i < BOMSIZE; i++)
		if (EOF == fputc(bom[i], tempFile)) return ERROR;

	int c = fgetc(inputFile);
	while (c != EOF) {
		if (EOF == fputc(c, tempFile)) return ERROR;
		c = fgetc(inputFile);
	}
	if (fclose(tempFile)) return ERROR;
	if (fclose(inputFile)) return ERROR;

	if (remove(filePath)) return ERROR;
	if (rename(tempFileName, filePath)) return ERROR;

	return SUCCESS;
}
