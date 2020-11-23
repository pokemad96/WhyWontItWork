#include <vector>
#include <time.h>

using std::vector;

#define TOTALPOINTS 100
#define ELECTRONCHARGE pow( 1.60217662, -19) 
#define ETHRESHOLDELECTRON (2.8 * ELECTRONCHARGE)
#define ETHRESHOLDHOLE (3.0 * ELECTRONCHARGE)

double getElectronPathLength(double eField);
double getHolePathLength(double eField);
void fileOut(vector<double> electrons, vector<double> holes);
double alphaCoefficient(double eField);
double betaCoefficient(double eField);
void fileOut2(double eFields[], int carriers[]);


int simulateCarriers(double eField, double width) {
	vector<double> electrons;
	vector<double> holes;
	// creates 2 lists of vectors which contain the position of each electron and hole that exists

	electrons.push_back(0);
	// create an electron with a start position at the origin
	int lastHole = 0;
	double distance;

	for (int x = 0; x < electrons.size(); x++) {
		// count through all the electrons that exist
		distance = getElectronPathLength(eField);
		electrons.at(x) += distance;
		if (electrons.at(x) < width) {
			// if the electron does an impact ionisation before reaching the end of the avalanche region
			// create a free electron and hole with position at the distance travelled
			electrons.push_back(electrons.at(x));
			holes.push_back(electrons.at(x));
		}
		for (int y = lastHole; y < holes.size(); y++) {
			// count from the last hole that was counted to the last hole that exists
			distance = getHolePathLength(eField);
			lastHole = holes.size();
			holes.at(y) -= distance;
			if (holes.at(y) > 0 ) {
				// if the hole does an impact ionisation before reaching the end of the avalanche region
				// create a free electron and hole with position at the distance travelled
				electrons.push_back(holes.at(y));
				holes.push_back(holes.at(y));
			}
		}
	}

	int numberCarriers = electrons.size() + holes.size();

	return numberCarriers;
}

void fileOut(double eField[], double gain[], double noiseFactor[], int dataSize) {
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/meanGain.csv", "w");
	if (err == 0) {
		fprintf(fp, "  Electric Field Strength:  ,  Mean Gain:  ,  Noise Factor: \n");
		for (int i = 0; i < dataSize; i++) {
			fprintf(fp, "%.10lf , %.10lf , %.10f \n", eField[i], gain[i], noiseFactor[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}

void fileOut2(double eFields[], int carriers[]) {
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/carriersSimulation.csv", "w");
	if (err == 0) {
		fprintf(fp, "  Electric Field:  ,  Number of Carriers:  \n");
		for (int i = 1; i < TOTALPOINTS; i++) {
			fprintf(fp, "%lf  ,  %d  \n", eFields[i], carriers[i]);
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}



