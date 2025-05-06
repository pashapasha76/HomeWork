#include "Rabbit.h"
#include <cstdlib>

const double Rabbit::MAX_ENERGY = 50.0;
const double Rabbit::ENERGY_COST_PER_UNIT = 0.5;
const double Rabbit::MAX_MOVEMENT = 3.0;
const double Rabbit::VIEW_RADIUS = 5.0;
const double Rabbit::CATCH_RADIUS = 1.0;

Rabbit::Rabbit(double x, double y, double energy)
    : Animal(x, y, energy) {}

void Rabbit::setEnergy(double value) {
    energy = std::min(value, MAX_ENERGY);
}

Creature* Rabbit::reproduce() {
    energy = energy/2;
    return new Rabbit(x, y, energy);
}

void Rabbit::print() const {
    std::cout << "Rabbit at (" << x << ", " << y << ") with energy " << energy << std::endl;
}

double Rabbit::getMaxEnergy() const {
    return MAX_ENERGY;
}

double Rabbit::getEnergyCostPerUnit() const {
    return ENERGY_COST_PER_UNIT;
}

double Rabbit::getMaxMovement() const {
    return MAX_MOVEMENT;
}

double Rabbit::getCatchRadius() const {
    return CATCH_RADIUS;
}

double Rabbit::getViewRadius() const {
    return VIEW_RADIUS;
}

std::string Rabbit::getTarget() const {
    return "Cabbage";
}

std::string Rabbit::getName() const {
    return "Rabbit";
}

void Rabbit::action(Area& area) {
    area.addCommand(new HuntCommand(this, area));
}

Creature* Rabbit::clone() const {
    return new Rabbit(*this);
}
