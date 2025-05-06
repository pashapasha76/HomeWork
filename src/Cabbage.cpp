#include "Cabbage.h"

const double Cabbage::MAX_ENERGY = 20.0;
const double Cabbage::ENERGY_INCREASE_PER_UNIT = 1.0;

Cabbage::Cabbage(double x, double y, double energy)
    : Creature(x, y, energy) {}

void Cabbage::setEnergy(double value) {
    energy = std::min(value, MAX_ENERGY);
}

double Cabbage::getMaxEnergy() const {
    return MAX_ENERGY;
}

Creature* Cabbage::reproduce() {
    energy = energy/2;
    return new Cabbage(x, y, energy);
}

void Cabbage::print() const {
    std::cout << "Cabbage at (" << x << ", " << y << ") with energy " << energy << std::endl;
}

void Cabbage::action(Area& area) {
    area.addCommand(new GrowCommand(this, area));
}

std::string Cabbage::getName() const {
    return "Cabbage";
}

Creature* Cabbage::clone() const {
    return new Cabbage(*this);
}
