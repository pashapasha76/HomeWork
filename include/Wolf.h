#ifndef WOLF_H
#define WOLF_H

#include "Animal.h"
#include "Area.h"

class Wolf : public Animal {
private:
    double aggressiveness;

    static const double MAX_ENERGY;
    static const double ENERGY_COST_PER_UNIT;
    static const double MAX_MOVEMENT;
    static const double VIEW_RADIUS;
    static const double CATCH_RADIUS;

public:
    Wolf(double x, double y, double energy, double aggressiveness);
    void setEnergy(double value) override;
    Creature* reproduce() override;

    bool operator<(const Wolf& other) const;
    bool operator==(const Wolf& other) const;
    bool operator<=(const Wolf& other) const;
    bool operator>=(const Wolf& other) const;
    bool operator>(const Wolf& other) const;
    bool operator!=(const Wolf& other) const;

    void print() const override;

    double getMaxEnergy() const override;
    
    double getEnergyCostPerUnit() const override;
    double getMaxMovement() const override;
    double getViewRadius() const override;
    double getCatchRadius() const override;
    Creature* clone() const override;
    std::string getTarget() const override;
    std::string getName() const override;
    double getAggressiveness() const;
    bool willHunt() const;

    void action(Area& area) override;
};

#endif
