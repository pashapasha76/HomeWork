#ifndef ANIMAL_H
#define ANIMAL_H

#include "Creature.h"

class Animal : public Creature {
public:
    Animal(double x, double y, double energy);
    virtual ~Animal() {}

    virtual bool move(double dx, double dy, double width, double height);
    virtual double getEnergyCostPerUnit() const = 0;
    virtual double getMaxMovement() const = 0;
    virtual double getViewRadius() const = 0;
    virtual double getCatchRadius() const = 0;
    virtual std::string getTarget() const = 0;
};

#endif 
