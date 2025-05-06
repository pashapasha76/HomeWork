#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <iostream>
#include "Area.h"

class Model {
private:
    int numSteps;
    int numRepetitions;
    double width;
    double height;
    int numWolves;
    int numRabbits;
    int numCabbages;
    double aggressiveness;
    std::vector<int> ecosystemLifetimes;
    std::vector<double> averageEnergyWolves;
    std::vector<double> averageEnergyRabbits;
    std::vector<double> averageEnergyCabbages;
    Area* currentArea;
    std::vector<std::vector<double>> wolfPositionsHistory;
    std::vector<std::vector<double>> rabbitPositionsHistory;
    std::vector<std::vector<double>> cabbagePositionsHistory;
    void collectResults(const Area& area, int t);
    void saveCurrentPositions();

public:
    Model(int numSteps, int numRepetitions, int numWolves, int numRabbits, 
          int numCabbages, double width, double height, double aggressiveness);
    ~Model();
    
    void run();
    void printResults() const;
    const std::vector<int>& getEcosystemLifetimes() const;
    const std::vector<double>& getAverageEnergyWolves() const;
    const std::vector<double>& getAverageEnergyRabbits() const;
    const std::vector<double>& getAverageEnergyCabbages() const;
    
    const std::vector<std::vector<double>>& getWolfPositionsHistory() const;
    const std::vector<std::vector<double>>& getRabbitPositionsHistory() const;
    const std::vector<std::vector<double>>& getCabbagePositionsHistory() const;
    
    void getCurrentWolfPositions(std::vector<double>& out_x, std::vector<double>& out_y) const;
    void getCurrentRabbitPositions(std::vector<double>& out_x, std::vector<double>& out_y) const;
    void getCurrentCabbagePositions(std::vector<double>& out_x, std::vector<double>& out_y) const;
    void saveFinalPositions(const Area& area);

};

#endif