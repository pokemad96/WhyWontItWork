#include <stdio.h>
#include <math.h>

#define ELECTRONCHARGE pow( 1.60217662, -19) 
#define ETHRESHOLDELECTRON (2.8 * ELECTRONCHARGE)
#define ETHRESHOLDHOLE (3.0 * ELECTRONCHARGE)
#define ALPHASTAR 0.210991
#define TOTALPOINTS 50000

double probabilityPathLength(double pathLength, double deadSpace);
void fileOut(double pathLength[], double probabilityPathLengths[]);

void testPDF() {
	double eField = 180000;
	double deadSpaceElectron = ETHRESHOLDELECTRON / ( ELECTRONCHARGE * eField );
	double deadSpaceHole = ETHRESHOLDHOLE / ( ELECTRONCHARGE * eField );

	double pathLength[TOTALPOINTS];
	double probabilityPathLengths[TOTALPOINTS];

	for (int i = 0; i < TOTALPOINTS; i++) {
		pathLength[i] = 0.0001 * i;
		probabilityPathLengths[i] = probabilityPathLength(pathLength[i], deadSpaceElectron);
	}

	fileOut(pathLength, probabilityPathLengths);
}

double probabilityPathLength(double pathLength, double deadSpace) {
	double probability;
	if (pathLength < deadSpace) {
		return 0;
	}
	else {
		probability = ALPHASTAR * exp(-(ALPHASTAR * (pathLength - deadSpace)));
		return probability;
	}
}

void fileOut(double pathLength[], double probabilityPathLengths[]) {
	FILE* fp;
	errno_t err;
	int dataSize = TOTALPOINTS;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/ionisationProbabilities.csv", "w");
	if (err == 0) {
		fprintf(fp, "Path Length: , Probability of Path Length: \n");
		for (int i = 0; i < dataSize; i++) {
			fprintf(fp, "%.10lf  ,  %.10lf   \n", pathLength[i], probabilityPathLengths[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}