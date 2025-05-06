#ifndef CREATURE_H
#define CREATURE_H

#include "MapObject.h"
class Area;

class Creature : public MapObject {
protected:
    double energy;
public:
    Creature(double x, double y, double energy);
    virtual ~Creature() {}

    virtual void setEnergy(double value);
    virtual void replenishEnergy(double amount);
    virtual bool isAlive() const;
    virtual bool shouldReproduce() const;
    virtual Creature* reproduce() = 0;
    double getEnergy() const { return energy; }
    virtual double getMaxEnergy() const = 0;
    virtual void action(Area& area) = 0;
    virtual std::string getName() const = 0;
    virtual Creature* clone() const = 0;
};

#endif 
