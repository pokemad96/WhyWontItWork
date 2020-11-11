#include <math.h>
#include <stdio.h>

#define EFIELD 850000
#define ELECTRONCHARGE pow( 1.60217662, -19) 
#define ETHRESHOLDELECTRON (2.8 * ELECTRONCHARGE)
#define ETHRESHOLDHOLE (3.0 * ELECTRONCHARGE)
#define WIDTH (0.8 * pow(10, -6))


void testPathLength(double edeadspace, double hdeadspace, double alphastar, double betastar);
double alphaCoefficient(double eField);
double betaCoefficient(double eField);
int simulateCarriers(double edeadspace, double hdeadspace, double alphastar, double betastar, double width);
void fileIn(float* var1, float* var2, float* var3, float* var4, float* var5);

int main() {
	float width;
	float BIVoltage;
	float SVoltage;
	float EVoltage;
	float VoltageS;
	fileIn(&width, &BIVoltage, &SVoltage, &EVoltage, &VoltageS);
	printf("%lf, %lf, %lf, %lf, %lf\n\n", width, BIVoltage, SVoltage, EVoltage, VoltageS);

	double edeadspace = ETHRESHOLDELECTRON / (ELECTRONCHARGE * EFIELD);
	double hdeadspace = ETHRESHOLDHOLE / (ELECTRONCHARGE * EFIELD);
	double alphastar = alphaCoefficient(EFIELD);
	double betastar = betaCoefficient(EFIELD);
	testPathLength(edeadspace, hdeadspace, alphastar, betastar);


	int numberCarriers = simulateCarriers(edeadspace, hdeadspace, alphastar, betastar, WIDTH);
	printf("%d\n", numberCarriers);
	return 0;
}