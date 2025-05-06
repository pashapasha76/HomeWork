#include "Creature.h"

Creature::Creature(double x, double y, double energy)
    : MapObject(x, y), energy(energy) {}

void Creature::setEnergy(double value) {
    energy = value;
}

void Creature::replenishEnergy(double amount) {
    energy += amount;
}

bool Creature::isAlive() const {
    return energy > 0;
}

bool Creature::shouldReproduce() const {
    return energy >= getMaxEnergy();
}
