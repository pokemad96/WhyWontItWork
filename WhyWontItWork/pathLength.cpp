#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define TOTALPOINTS 5000
// diefines the number of points that the program will calculate and plot in csv file

void fileOut(int inverseEField[], double alphaStar[], double betaStar[]);

double getRand() {
	// returns a random double between 0 and 1
	double randN;
	randN = (float) (rand()) / RAND_MAX;
	return randN;
}

double getPathLength(double deadspace, double ionCoefficient) {
	// uses deadspace and either alpha or beta coefficient to calculate a random path length
	double pathLength;

	pathLength = deadspace - (log (getRand()) / ionCoefficient);
	pathLength /= 100;
	return pathLength;
}

double getMean(double values[]) {
	double total = 0;
	double mean;
	for (int i = 0; i < TOTALPOINTS; i++) {
		total += values[i];
	}
	mean = total / TOTALPOINTS;
	return mean;
}

void testPathLength(double edeadspace, double hdeadspace, double alphastar, double betastar) {
	int testNumber[TOTALPOINTS];

	double pathLengths[TOTALPOINTS];
	double pathLengths2[TOTALPOINTS];
	for (int i = 0; i < TOTALPOINTS; i++) {
		testNumber[i] = i + 1;
	}
	for (int i = 0; i < TOTALPOINTS; i++) {
		pathLengths[i] = getPathLength(edeadspace, alphastar);
	}
	for (int i = 0; i < TOTALPOINTS; i++) {
		pathLengths2[i] = getPathLength(hdeadspace, betastar);
	}

	printf("%.10lf\n", getMean(pathLengths));

	fileOut(testNumber, pathLengths, pathLengths2);
}

void fileOut(int inverseEField[], double alphaStar[], double betaStar[]) {
	FILE* fp;
	errno_t err;
	int dataSize = TOTALPOINTS;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/pathLengths.csv", "w");
	if (err == 0) {
		fprintf(fp, "Test Number: ,  Electron Path Length: ,  Hole Path Length:   \n");
		for (int i = 0; i < dataSize; i++) {
			fprintf(fp, "%d  ,  %.10lf  ,  %.10lf    \n", inverseEField[i], alphaStar[i], betaStar[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}