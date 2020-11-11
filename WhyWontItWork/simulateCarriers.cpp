#include <vector>

using std::vector;

double getPathLength(double deadspace, double ionCoefficient);
void fileOut(vector<double> electrons, vector<double> holes);

int simulateCarriers(double edeadspace, double hdeadspace, double alphastar, double betastar, double width) {
	vector<double> electrons;
	vector<double> holes;
	// creates 2 lists of vectors which contain the position of each electron and hole that exists
	vector<double> electronStart;
	vector<double> holeStart;
	// creates 2 lists of vectors which contain the starting positions of every vector that exists

	electrons.push_back(0);
	electronStart.push_back(0);
	// create an electron with a start position at the origin
	int lastHole = 0;

	for (int x = 0; x < electrons.size(); x++) {
		// count through all the electrons that exist
		double distance = getPathLength(edeadspace, alphastar);
		if (distance < (width - electrons.at(x))) {
			// if the electron does an impact ionisation before reaching the end of the avalanche region
			// create a free electron and hole with position at the distance travelled
			electrons.at(x) += distance;
			electrons.push_back(electrons.at(x));
			holes.push_back(electrons.at(x));
			electronStart.push_back(electrons.at(x));
		}
		else {
			electronStart.push_back(electrons.at(x));
		}
		for (int y = lastHole; y < holes.size(); y++) {
			// count from the last hole that was counted to the last hole that exists
			distance = getPathLength(hdeadspace, betastar);
			lastHole = holes.size();
			if (distance < (width - holes.at(y))) {
				// if the hole does an impact ionisation before reaching the end of the avalanche region
				// create a free electron and hole with position at the distance travelled
				holes.at(y) += distance;
				electrons.push_back(holes.at(y));
				holes.push_back(holes.at(y));
				holeStart.push_back(holes.at(y) + distance);
			}
			else {
				holeStart.push_back(holes.at(y) + distance);
			}
			printf("I am doing something!\n");
		}
	}

	int numberCarriers = electrons.size() + holes.size();

	printf("%d\n", electronStart.size());
	printf("%d\n", holeStart.size());

	fileOut(electronStart, holeStart);
	return numberCarriers;
}

void fileOut(vector<double> electrons, vector<double> holes) {
	FILE* fp;
	errno_t err;

	err = fopen_s(&fp, "C:/Users/Johnathan/Documents/_Uni Stuff/Individual Project/pathLengthsSimulation.csv", "w");
	if (err == 0) {
		fprintf(fp, "  Carrier Number:  ,  Carrier Distance  \n");
		fprintf(fp, " 1 ,  %.10lf  \n", electrons.at(0));
		for (int i = 1; i < 10; i++) {
			fprintf(fp, "%d  ,  %.10lf  \n %d  ,  %.10lf    \n", 2 * i ,electrons.at(i), 2 * i + 1, holes.at(i-1));
		}
	}
	else {
		printf("There was an error opening the file!");
	}
}
