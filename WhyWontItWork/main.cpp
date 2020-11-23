#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EFIELD 400000
#define WIDTH (1.0 * pow(10, -6))


void testPathLength();
void testPathLength2();
double alphaCoefficient(double eField);
double betaCoefficient(double eField);
int simulateCarriers(double eField, double width);
void fileIn(float* var1, float* var2, float* var3, float* var4, float* var5);
void testRand();
double getMeanGain(double eField, double width);
double electronDeadSpace(double eField);
void testGains(double width);

int main() {
	// set seed for rand
	srand(time(0));

	double gain;
	double eField = EFIELD;

	testGains(WIDTH);

	return 0;
}

