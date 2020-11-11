#include <stdio.h>
#include <math.h>

#define TOTALPOINTS 100

double alphaCoefficient(double eField);
double betaCoefficient(double eField);
void fileOut(double inverseEField[],  double alphaStar[], double betaStar[]);

int testCoefficient () {
	double eField[TOTALPOINTS];
	double alphaStar[TOTALPOINTS];
	double betaStar[TOTALPOINTS];
	double inverseEField[TOTALPOINTS];

	double step = (850000 - 180000) / TOTALPOINTS;

	for (int i = 0; i < TOTALPOINTS; i++) {
		eField[i] = double(180000) + i * step;
	}

	for (int i = 0; i < TOTALPOINTS; i++) {
		inverseEField[i] = 1 / eField[i];
		alphaStar[i] = alphaCoefficient(eField[i]);
		betaStar[i] = betaCoefficient(eField[i]);
	}
	fileOut(inverseEField, alphaStar, betaStar);

	return 0;
}

double alphaCoefficient(double eField) {
	double alphaStar;
	alphaStar = 1.41 * 1000000 * exp( -pow( (1.69 * 1000000 / eField),  1.23) );
	return alphaStar;
}

double betaCoefficient(double eField) {
	double betaStar;
	betaStar = 2.11 * 1000000 * exp( -pow( (1.77 * 1000000 / eField), 1.15) );
	return betaStar;
}

void fileOut(double inverseEField[], double alphaStar[], double betaStar[]) {
	FILE* fp;
	errno_t err;
	int dataSize = TOTALPOINTS;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/ionisationCoefficients.csv", "w");
	if (err == 0) {
		fprintf(fp, "inverse E field: ,  alpha_Star: ,  beta_Star:   \n");
		for (int i = 0; i < dataSize; i++) {
			fprintf(fp, "%.10lf  ,  %.10lf  ,  %.10lf    \n", inverseEField[i], alphaStar[i], betaStar[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}