#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define TOTALPOINTS 5000

double getRand() {
	// returns a random double between 0 and 1
	double randN;
	randN = (double)(rand()) / (double)RAND_MAX;
	return randN;
}

void fileOut(double randNum[]) {
	FILE* fp;
	errno_t err;
	int dataSize = TOTALPOINTS;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/randomFunction.csv", "w");
	if (err == 0) {
		fprintf(fp, "Trial Number: ,  Random Number: \n");
		for (int i = 0; i < dataSize; i++) {
			fprintf(fp, "%d  ,  %.10lf  \n", i, randNum[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}

void testRand() {
	double randNum[TOTALPOINTS];
	for (int i = 0; i < TOTALPOINTS; i++) {
		randNum[i] = getRand();
	}

	fileOut(randNum);
}


