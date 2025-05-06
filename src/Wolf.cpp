#include "Wolf.h"
#include <cstdlib>


const double Wolf::MAX_ENERGY = 100.0;
const double Wolf::ENERGY_COST_PER_UNIT = 1.0;
const double Wolf::MAX_MOVEMENT = 5.0;
const double Wolf::VIEW_RADIUS = 10.0;
const double Wolf::CATCH_RADIUS = 2.0;

Wolf::Wolf(double x, double y, double energy, double aggressiveness)
    : Animal(x, y, energy), aggressiveness(aggressiveness) {}

void Wolf::setEnergy(double value) {
    energy = std::min(value, MAX_ENERGY);
}

Creature* Wolf::reproduce() {
    energy = energy/2;
    return new Wolf(x, y, energy, aggressiveness);
}

bool Wolf::operator<(const Wolf& other) const {
    return energy < other.energy;
}

bool Wolf::operator==(const Wolf& other) const {
    return energy == other.energy;
}

bool Wolf::operator<=(const Wolf& other) const {
    return energy <= other.energy;
}

bool Wolf::operator>=(const Wolf& other) const {
    return energy >= other.energy;
}

bool Wolf::operator>(const Wolf& other) const {
    return energy > other.energy;
}

bool Wolf::operator!=(const Wolf& other) const {
    return energy != other.energy;
}

void Wolf::print() const {
    std::cout << "Wolf at (" << x << ", " << y << ") with energy " << energy << std::endl;
}

double Wolf::getMaxEnergy() const {
    return MAX_ENERGY;
}

double Wolf::getEnergyCostPerUnit() const {
    return ENERGY_COST_PER_UNIT;
}

double Wolf::getMaxMovement() const {
    return MAX_MOVEMENT;
}

double Wolf::getViewRadius() const {
    return VIEW_RADIUS;
}

double Wolf::getCatchRadius() const {
    return CATCH_RADIUS;
}

std::string Wolf::getTarget() const {
    return "Rabbit";
}

std::string Wolf::getName() const {
    return "Wolf";
}

bool Wolf::willHunt() const {
    return aggressiveness > std::rand() / static_cast<double>(RAND_MAX);
}

void Wolf::action(Area& area) {
    if (willHunt()) {
        area.addCommand(new HuntCommand(this, area));
    }
}

Creature* Wolf::clone() const {
    return new Wolf(*this);
}


double Wolf::getAggressiveness() const {
    return aggressiveness; 
}