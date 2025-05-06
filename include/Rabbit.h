#ifndef RABBIT_H
#define RABBIT_H

#include "Animal.h"
#include "Area.h"

class Rabbit : public Animal {
private:
    static const double MAX_ENERGY;
    static const double ENERGY_COST_PER_UNIT;
    static const double MAX_MOVEMENT;
    static const double VIEW_RADIUS;
    static const double CATCH_RADIUS;

public:
    Rabbit(double x, double y, double energy);
    void setEnergy(double value) override;
    Creature* reproduce() override;
    void print() const override;
    double getMaxEnergy() const override;
    double getEnergyCostPerUnit() const override;
    double getMaxMovement() const override;
    double getCatchRadius() const override;
    double getViewRadius() const override;
    std::string getTarget() const override;
    std::string getName() const override;
    void action(Area& area) override;
    Creature* clone() const override;
};

#endif
