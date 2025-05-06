#include "Model.h"

int main() {
    int numSteps = 100;
    int numRepetitions = 3;
    int numWolves = 10;
    int numRabbits = 100;
    int numCabbages = 200;
    double width = 100.0;
    double height = 100.0;
    double aggressiveness = 0.5;

    for (float i = 1; i < 11; i++){
        std::cout << "Aggressiveness: "<< i/10 << std::endl;
        Model model(numSteps, numRepetitions, numWolves, numRabbits, numCabbages, width, height, i/10);
        model.run();
        model.printResults();
    };

    return 0;
}
