#include <math.h>

#define TESTS 301
#define ITERATIONS 10000

int simulateCarriers(double eField, double width);
double getMean(double values[], int totalValues);
void fileOut(double eField[], double gain[], double noiseFactor[], int dataSize);

double getMeanGain(double eField, double width) {
	double carriers[ITERATIONS];
	double gain;

	for (int i = 0; i < ITERATIONS; i++) {
		carriers[i] = (double)simulateCarriers(eField, width);
	}
	gain = getMean(carriers, ITERATIONS);
	return gain;
}

double getNoiseFactor(double eField, double width, double meanGain) {
	double noiseFactor;
	double carriers[ITERATIONS];
	double gain;

	for (int i = 0; i < ITERATIONS; i++) {
		carriers[i] = pow((double)simulateCarriers(eField, width), 2);
	}

	noiseFactor = getMean(carriers, ITERATIONS) / (pow(meanGain, 2));
	return noiseFactor;
}

void testGains(double width) {
	double gain[TESTS];
	double eField[TESTS];
	double noiseFactor[TESTS];

	for (int i = 0; i < TESTS; i++) {
		eField[i] = (double)180000 + (double)1000 * (double)(i);
	}

	for (int i = 0; i < TESTS; i++) {
		gain[i] = getMeanGain(eField[i], width);
		noiseFactor[i] = getNoiseFactor(eField[i], width, gain[i]);
	}

	fileOut(eField, gain, noiseFactor, TESTS);
}