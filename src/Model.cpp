#include "Model.h"
#include <algorithm>
#include <numeric>

Model::Model(int numSteps, int numRepetitions, int numWolves, int numRabbits,
             int numCabbages, double width, double height, double aggressiveness)
    : numSteps(numSteps), numRepetitions(numRepetitions), numWolves(numWolves),
      numRabbits(numRabbits), numCabbages(numCabbages), width(width),
      height(height), aggressiveness(aggressiveness), currentArea(nullptr) {}

Model::~Model() {
    delete currentArea;
}

void Model::run() {
    wolfPositionsHistory.clear();
    rabbitPositionsHistory.clear();
    cabbagePositionsHistory.clear();
    
    for (int i = 0; i < numRepetitions; ++i) {
        delete currentArea;
        currentArea = new Area(width, height, numWolves, numRabbits, numCabbages, aggressiveness);
        
        int t = 0;
        for (int step = 0; step < numSteps; ++step) {
            currentArea->step();
            
            if (!currentArea->isSystemAlive()) break;
            t++;
        }
        saveFinalPositions(*currentArea);
        collectResults(*currentArea, t);
    }
}

void Model::saveCurrentPositions() {
    std::vector<double> wolf_x, wolf_y;
    std::vector<double> rabbit_x, rabbit_y;
    std::vector<double> cabbage_x, cabbage_y;
    
    getCurrentWolfPositions(wolf_x, wolf_y);
    getCurrentRabbitPositions(rabbit_x, rabbit_y);
    getCurrentCabbagePositions(cabbage_x, cabbage_y);
    
    std::vector<double> wolf_flat;
    for (size_t i = 0; i < wolf_x.size(); ++i) {
        wolf_flat.push_back(wolf_x[i]);
        wolf_flat.push_back(wolf_y[i]);
    }
    wolfPositionsHistory.push_back(wolf_flat);
    
    std::vector<double> rabbit_flat;
    for (size_t i = 0; i < rabbit_x.size(); ++i) {
        rabbit_flat.push_back(rabbit_x[i]);
        rabbit_flat.push_back(rabbit_y[i]);
    }
    rabbitPositionsHistory.push_back(rabbit_flat);
    
    std::vector<double> cabbage_flat;
    for (size_t i = 0; i < cabbage_x.size(); ++i) {
        cabbage_flat.push_back(cabbage_x[i]);
        cabbage_flat.push_back(cabbage_y[i]);
    }
    cabbagePositionsHistory.push_back(cabbage_flat);
}

void Model::getCurrentWolfPositions(std::vector<double>& out_x, std::vector<double>& out_y) const {
    out_x.clear();
    out_y.clear();
    if (currentArea) {
        currentArea->getWolfPositions(out_x, out_y);
    }
}

void Model::getCurrentRabbitPositions(std::vector<double>& out_x, std::vector<double>& out_y) const {
    out_x.clear();
    out_y.clear();
    if (currentArea) {
        currentArea->getRabbitPositions(out_x, out_y);
    }
}

void Model::getCurrentCabbagePositions(std::vector<double>& out_x, std::vector<double>& out_y) const {
    out_x.clear();
    out_y.clear();
    if (currentArea) {
        currentArea->getCabbagePositions(out_x, out_y);
    }
}

const std::vector<std::vector<double>>& Model::getWolfPositionsHistory() const {
    return wolfPositionsHistory;
}

const std::vector<std::vector<double>>& Model::getRabbitPositionsHistory() const {
    return rabbitPositionsHistory;
}

const std::vector<std::vector<double>>& Model::getCabbagePositionsHistory() const {
    return cabbagePositionsHistory;
}

void Model::collectResults(const Area& area, int t) {
    ecosystemLifetimes.push_back(t);
    
    averageEnergyWolves.push_back(area.getMeanWolfsEnergy());
    averageEnergyRabbits.push_back(area.getMeanRabbitsEnergy());
    averageEnergyCabbages.push_back(area.getMeanCabbagesEnergy());
}

const std::vector<int>& Model::getEcosystemLifetimes() const {
    return ecosystemLifetimes;
}

const std::vector<double>& Model::getAverageEnergyWolves() const {
    return averageEnergyWolves;
}

const std::vector<double>& Model::getAverageEnergyRabbits() const {
    return averageEnergyRabbits;
}

const std::vector<double>& Model::getAverageEnergyCabbages() const {
    return averageEnergyCabbages;
}

void Model::printResults() const {
    if (ecosystemLifetimes.empty() || 
        averageEnergyWolves.empty() || 
        averageEnergyRabbits.empty() || 
        averageEnergyCabbages.empty()) {
        std::cout << "No simulation results available. Run the simulation first." << std::endl;
        return;
    }

    double avgLifetime = std::accumulate(ecosystemLifetimes.begin(), 
                                       ecosystemLifetimes.end(), 0.0) 
                       / ecosystemLifetimes.size();

    double avgWolfEnergy = std::accumulate(averageEnergyWolves.begin(),
                                         averageEnergyWolves.end(), 0.0)
                        / averageEnergyWolves.size();

    double avgRabbitEnergy = std::accumulate(averageEnergyRabbits.begin(),
                                           averageEnergyRabbits.end(), 0.0)
                          / averageEnergyRabbits.size();

    double avgCabbageEnergy = std::accumulate(averageEnergyCabbages.begin(),
                                            averageEnergyCabbages.end(), 0.0)
                           / averageEnergyCabbages.size();

    std::cout << "\n=== Simulation Results ===\n";
    std::cout << "Average Ecosystem Lifetime: " << avgLifetime << " steps\n";
    std::cout << "Average Energy Levels:\n";
    std::cout << "  Wolves:   " << avgWolfEnergy << "\n";
    std::cout << "  Rabbits:  " << avgRabbitEnergy << "\n";
    std::cout << "  Cabbages: " << avgCabbageEnergy << "\n";
    std::cout << "=========================\n";

    std::cout << "\nDetailed Statistics:\n";
    std::cout << "Number of simulations: " << numRepetitions << "\n";
    std::cout << "Steps per simulation:  " << numSteps << "\n";
    std::cout << "Initial populations:\n";
    std::cout << "  Wolves:   " << numWolves << "\n";
    std::cout << "  Rabbits:  " << numRabbits << "\n";
    std::cout << "  Cabbages: " << numCabbages << "\n";
    std::cout << "Area dimensions: " << width << " x " << height << "\n";
    std::cout << "Wolf aggressiveness: " << aggressiveness << "\n";
}

void Model::saveFinalPositions(const Area& area) {
    std::vector<double> wolf_x, wolf_y;
    area.getWolfPositions(wolf_x, wolf_y);
    std::vector<double> wolf_flat;
    for (size_t i = 0; i < wolf_x.size(); ++i) {
        wolf_flat.push_back(wolf_x[i]);
        wolf_flat.push_back(wolf_y[i]);
    }
    wolfPositionsHistory.push_back(wolf_flat);

    std::vector<double> rabbit_x, rabbit_y;
    area.getRabbitPositions(rabbit_x, rabbit_y);
    std::vector<double> rabbit_flat;
    for (size_t i = 0; i < rabbit_x.size(); ++i) {
        rabbit_flat.push_back(rabbit_x[i]);
        rabbit_flat.push_back(rabbit_y[i]);
    }
    rabbitPositionsHistory.push_back(rabbit_flat);

    std::vector<double> cabbage_x, cabbage_y;
    area.getCabbagePositions(cabbage_x, cabbage_y);
    std::vector<double> cabbage_flat;
    for (size_t i = 0; i < cabbage_x.size(); ++i) {
        cabbage_flat.push_back(cabbage_x[i]);
        cabbage_flat.push_back(cabbage_y[i]);
    }
    cabbagePositionsHistory.push_back(cabbage_flat);
}