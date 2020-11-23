#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define TOTALPOINTS 5000
// defines the number of points that the program will calculate and plot in csv file

void testPathLength2();
void fileOut2(double randNum[]);
double electronDeadSpace(double eField);
double holeDeadSpace(double eField);
double alphaCoefficient(double eField);
double betaCoefficient(double eField);
void fileOut(int inverseEField[], double alphaStar[], double betaStar[]);
double getRand();

void fileOut(double inverseEField[], double alphaStar[], double betaStar[]) {
	printf("I'm printing something\n");
	FILE* fp;
	errno_t err;
	int dataSize = 67;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/meanValues.csv", "w");
	if (err == 0) {
		fprintf(fp, "Electric Field: ,  Electron Path Length Mean: ,  Hole Path Length Mean:   \n");
		for (int i = 0; i < dataSize; i++) {
			fprintf(fp, "%.10lf  ,  %.10lf  ,  %.10lf  \n", inverseEField[i], alphaStar[i], betaStar[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}

double getElectronPathLength(double eField) {
	// uses deadspace and either alpha or beta coefficient to calculate a random path length
	double pathLength;
	double deadSpace = electronDeadSpace(eField);
	double ionCoefficient = alphaCoefficient(eField);

	pathLength = deadSpace - (log (getRand()) / ionCoefficient);
	pathLength /= 100;
	return pathLength;
}

double getHolePathLength(double eField) {
	// uses deadspace and either alpha or beta coefficient to calculate a random path length
	double pathLength;
	double deadSpace = holeDeadSpace(eField);
	double ionCoefficient = betaCoefficient(eField);

	pathLength = deadSpace - (log(getRand()) / ionCoefficient);
	pathLength /= 100;
	return pathLength;
}

double getMean(double values[], int totalValues) {
	double total = 0;
	double mean;
	double arraySize = (double) totalValues;
	for (int i = 0; i < totalValues; i++) {
		total += values[i];
	}
	mean = total / arraySize;
	return mean;
}

void testPathLength() {
	int testNumber[TOTALPOINTS];

	double pathLengths[TOTALPOINTS];
	double pathLengths2[TOTALPOINTS];
	double mean[67];
	double mean2[67];
	double eField[67];
	
	for (int i = 0; i < 67; i++) {
		eField[i] = (double)180000 + (double)10000 * (double)(i);
	}

	for (int i = 0; i < 67; i++) {
		for (int j = 0; j < TOTALPOINTS; j++) {
			pathLengths[j] = getElectronPathLength(eField[i]);
		}
		for (int j = 0; j < TOTALPOINTS; j++) {
			pathLengths2[j] = getHolePathLength(eField[i]);
		}
		mean[i] = getMean(pathLengths, TOTALPOINTS);
		mean2[i] = getMean(pathLengths2, TOTALPOINTS);
	}

	fileOut(eField, mean, mean2);
}

void testPathLength2() {
	int testNumber[TOTALPOINTS];

	double pathLengths[TOTALPOINTS];
	double pathLengths2[TOTALPOINTS];
	double eField = 600000;

	for (int i = 0; i < TOTALPOINTS; i++) {
		pathLengths[i] = getElectronPathLength(eField);
		testNumber[i] = i;
	}
	for (int i = 0; i < TOTALPOINTS; i++) {
		pathLengths2[i] = getHolePathLength(eField);
	}

	fileOut(testNumber, pathLengths, pathLengths);
}


void fileOut2(double randNum[]) {
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