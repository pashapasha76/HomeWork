#ifndef CABBAGE_H
#define CABBAGE_H

#include "Creature.h"
#include "Area.h"

class Cabbage : public Creature {
private:
    static const double MAX_ENERGY;
    static const double ENERGY_INCREASE_PER_UNIT;

public:
    Cabbage(double x, double y, double energy);
    void setEnergy(double value) override;
    double getMaxEnergy() const override;
    Creature* reproduce() override;
    void print() const override;
    void action(Area& area) override;
    std::string getName() const override;
    Creature* clone() const override;
    double getGrowEnergy() const {return ENERGY_INCREASE_PER_UNIT;};
};

#endif 
