#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <fstream>

using std::fstream;

#define TOTALPOINTS

double getNextDouble(FILE* fp);

void fileIn(float* var1, float* var2, float* var3, float* var4, float* var5) {
	FILE* fp;
	errno_t err;
	int dataSize = 0;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/inputFile.txt", "r");
	if (err == 0) {
		*var1 = getNextDouble(fp);
		*var2 = getNextDouble(fp);
		*var3 = getNextDouble(fp);
		*var4 = getNextDouble(fp);
		*var5 = getNextDouble(fp);
	}
	else {
		printf("There was an error opening the file!");
	}
}

double getNextDouble(FILE* fp){
	char buf[20];
	char c;
	int i = 0;
	char* eptr;
	while ((c = fgetc(fp)) != '\n') {
		if (c <= '9' && c > '0') {
			buf[i] = c;
			i++;
		}
	}
	buf[i] = '\0';
	return (strtod(buf, &eptr));
}

