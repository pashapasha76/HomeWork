#include "Animal.h"
#include <cmath>

Animal::Animal(double x, double y, double energy)
    : Creature(x, y, energy) {}

bool Animal::move(double x_t, double y_t, double width, double height) {
    double dx = x_t - x;
    double dy = y_t - y;
    double distance = std::sqrt(dx * dx + dy * dy);
    if (distance > getMaxMovement()) {
        dx =  getMaxMovement() * dx/distance;
        dx =  getMaxMovement() * dy/distance;
        distance = std::sqrt(dx * dx + dy * dy);
    }
    energy -= distance * getEnergyCostPerUnit();
    if (energy < 0) {
        energy = 0;
    }
    x = std::fmod(x + dx + width, width);
    y = std::fmod(y + dy + height, height);
    return true;
}
