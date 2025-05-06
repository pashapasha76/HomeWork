#include "Area.h"
#include "Command.h"
#include "Wolf.h"
#include "Rabbit.h"
#include "Cabbage.h"
#include <cmath>
#include <algorithm>
#include <random>

Area::Area(double width, double height, int numWolves, int numRabbits, int numCabbages, double aggressiveness)
    : width(width), height(height) {
    generateInitialState(numWolves, numRabbits, numCabbages, aggressiveness);
}

Area::~Area() {
    for (Creature* creature : creatures) {
        delete creature;
    }
}

Area::Area(const Area& other)
    : width(other.width), height(other.height), invoker(other.invoker) {
    for (Creature* creature : other.creatures) {
        addCreature(creature->clone());
    }
}

Area& Area::operator=(const Area& other) {
    if (this != &other) {
        for (Creature* creature : creatures) {
            delete creature;
        }
        creatures.clear();

        width = other.width;
        height = other.height;
        invoker = other.invoker;
        for (Creature* creature : other.creatures) {
            addCreature(creature->clone());
        }
    }
    return *this;
}

void Area::generateInitialState(int numWolves, int numRabbits, int numCabbages, double aggressiveness) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> disX(0, width);
    std::uniform_real_distribution<> disY(0, height);

    for (int i = 0; i < numWolves; ++i) {
        addCreature(new Wolf(disX(gen), disY(gen), 100.0, aggressiveness));
    }

    for (int i = 0; i < numRabbits; ++i) {
        addCreature(new Rabbit(disX(gen), disY(gen), 50.0));
    }

    for (int i = 0; i < numCabbages; ++i) {
        addCreature(new Cabbage(disX(gen), disY(gen), 20.0));
    }
}

void Area::addCreature(Creature* creature) {
    creatures.push_back(creature);
}

void Area::step() {
    for (Creature* creature : creatures) {  
        if (creature->shouldReproduce()) {
            addCommand(new ReproduceCommand(creature, creatures));
        }
        creature->action(*this); 
        
    }
    invoker.executeCommands();

    creatures.erase(
        std::remove_if(creatures.begin(), creatures.end(), [](Creature* creature) {
            if (!creature->isAlive()){
            delete creature;
            return true;
            }
            return false;
        }),
        creatures.end()
    );

    saveStep();
}

void Area::print() const {

    std::cout << "Wolfs Energy: " << getMeanWolfsEnergy() << ", Rabbits Energy: " << getMeanRabbitsEnergy() << ", Cabbages Energy: " << getMeanCabbagesEnergy() << std::endl;
    std::cout << "Number of wolfs: " << getNumWolfs() << ", Number of rabbits: " << getNumRabbits() << ", Number of cabbages: " << getNumCabbages() << std::endl;

}

double Area::getMeanWolfsEnergy() const{
    double generalEnergy = 0;
    int k = 0;
    for (Creature* creature : creatures) {
        if (creature->getName() == "Wolf"){
            generalEnergy+=creature->getEnergy();
            k+=1;
        }
    }
    return (k== 0) ?  0 : (generalEnergy/k);
}

double Area::getMeanCabbagesEnergy() const{
    double generalEnergy = 0;
    int k = 0;
    for (Creature* creature : creatures) {
        if (creature->getName() == "Cabbage"){
            generalEnergy+=creature->getEnergy();
            k+=1;
        }
    }
    return (k == 0) ?  0 : (generalEnergy/k);
}

double Area::getMeanRabbitsEnergy() const{
    double generalEnergy = 0;
    int k = 0;
    for (Creature* creature : creatures) {
        if (creature->getName() == "Rabbit"){
            generalEnergy+=creature->getEnergy();
            k+=1;
        }
    }
    return (k == 0) ?  0 : (generalEnergy/k);
}

int Area::getNumWolfs() const{
    int k = 0;
    for (Creature* creature : creatures) {
        if (creature->getName() == "Wolf"){
            k+=1;
        }
    }
    return k;
}

int Area::getNumCabbages() const{
    int k = 0;
    for (Creature* creature : creatures) {
        if (creature->getName() == "Cabbage"){
            k+=1;
        }
    }
    return k;
}

int Area::getNumRabbits() const{
    int k = 0;
    for (Creature* creature : creatures) {
        if (creature->getName() == "Rabbit"){
            k+=1;
        }
    }
    return k;
}

bool Area::isSystemAlive() const{
    return ((getNumRabbits() > 0) || (getNumWolfs() > 0));
}

void Area::getWolfPositions(std::vector<double>& out_x, std::vector<double>& out_y) const {
    out_x.clear();
    out_y.clear();
    for (const auto& creature : creatures) {
        if (dynamic_cast<Wolf*>(creature)) {
            out_x.push_back(creature->getX());
            out_y.push_back(creature->getY());
        }
    }
}

void Area::getRabbitPositions(std::vector<double>& out_x, std::vector<double>& out_y) const {
    out_x.clear();
    out_y.clear();
    for (const auto& creature : creatures) {
        if (dynamic_cast<Rabbit*>(creature)) {
            out_x.push_back(creature->getX());
            out_y.push_back(creature->getY());
        }
    }
}

void Area::getCabbagePositions(std::vector<double>& out_x, std::vector<double>& out_y) const {
    out_x.clear();
    out_y.clear();
    for (const auto& creature : creatures) {
        if (dynamic_cast<Cabbage*>(creature)) {
            out_x.push_back(creature->getX());
            out_y.push_back(creature->getY());
        }
    }
}

void Area::saveStep() {
    std::vector<double> wolves, rabbits, cabbages;
    
    for (const auto& creature : creatures) {
        if (dynamic_cast<Wolf*>(creature)) {
            wolves.push_back(creature->getX());
            wolves.push_back(creature->getY());
        } 
        else if (dynamic_cast<Rabbit*>(creature)) {
            rabbits.push_back(creature->getX());
            rabbits.push_back(creature->getY());
        }
        else if (dynamic_cast<Cabbage*>(creature)) {
            cabbages.push_back(creature->getX());
            cabbages.push_back(creature->getY());
        }
    }

    wolfStepHistory.push_back(wolves);
    rabbitStepHistory.push_back(rabbits);
    cabbageStepHistory.push_back(cabbages);
}

const std::vector<std::vector<double> >& Area::getWolfStepHistory() const { return wolfStepHistory; }
const std::vector<std::vector<double> >& Area::getRabbitStepHistory() const { return rabbitStepHistory; }
const std::vector<std::vector<double> >& Area::getCabbageStepHistory() const { return cabbageStepHistory; }
