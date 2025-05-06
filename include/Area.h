#ifndef AREA_H
#define AREA_H

#include <vector>
#include "Creature.h"
#include "Invoker.h"

class Area {
private:
    std::vector<Creature*> creatures;
    double width, height;
    Invoker invoker;
    std::vector<std::vector<double> > wolfStepHistory;
    std::vector<std::vector<double> > rabbitStepHistory;
    std::vector<std::vector<double> > cabbageStepHistory;
public:
    Area(double width, double height, int numWolves, int numRabbits, int numCabbages, double aggressiveness);
    ~Area();
    Area(const Area& other);
    Area& operator=(const Area& other);
    void addCreature(Creature* creature);
    void step();
    void print() const;
    const std::vector<Creature*>& getCreatures() const { return creatures; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    void addCommand(Command* command) { invoker.addCommand(command); }
    void generateInitialState(int numWolves, int numRabbits, int numCabbages, double aggressiveness);
    double getMeanWolfsEnergy() const; 
    double getMeanRabbitsEnergy() const; 
    double getMeanCabbagesEnergy() const;
    int getNumWolfs() const; 
    int getNumRabbits() const; 
    int getNumCabbages() const;
    bool isSystemAlive() const;
    void getWolfPositions(std::vector<double>& out_x, std::vector<double>& out_y) const;
    void getRabbitPositions(std::vector<double>& out_x, std::vector<double>& out_y) const;
    void getCabbagePositions(std::vector<double>& out_x, std::vector<double>& out_y) const;
    const std::vector<std::vector<double> >& getWolfStepHistory() const;
    const std::vector<std::vector<double> >& getRabbitStepHistory() const;
    const std::vector<std::vector<double> >& getCabbageStepHistory() const;
    void saveStep();
};

#endif 
