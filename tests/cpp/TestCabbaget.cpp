#include <cassert>
#include "Cabbage.h"
#include "Area.h"

void testCabbageCreation() {
    Cabbage cabbage(1.0, 2.0, 10.0);
    assert(cabbage.getX() == 1.0);
    assert(cabbage.getY() == 2.0);
    assert(cabbage.getEnergy() == 10.0);
    assert(cabbage.getId() == 0);
}

void testCabbageEnergy() {
    Cabbage cabbage(1.0, 2.0, 10.0);
    cabbage.setEnergy(15.0);
    assert(cabbage.getEnergy() == 15.0);
    cabbage.setEnergy(25.0);
    assert(cabbage.getEnergy() == cabbage.getMaxEnergy());
}

void testCabbageReproduction() {
    Cabbage cabbage(1.0, 2.0, cabbage.getMaxEnergy());
    Creature* newCabbage = cabbage.reproduce();
    assert(newCabbage != nullptr);
    assert(newCabbage->getEnergy() == cabbage.getMaxEnergy() / 2);
    assert(cabbage.getEnergy() == cabbage.getMaxEnergy() / 2);
    delete newCabbage;
}


void testCabbageClone() {
    Cabbage cabbage(1.0, 2.0, 10.0);
    Creature* clonedCabbage = cabbage.clone();
    assert(clonedCabbage != nullptr);
    assert(clonedCabbage->getX() == cabbage.getX());
    assert(clonedCabbage->getY() == cabbage.getY());
    assert(clonedCabbage->getEnergy() == cabbage.getEnergy());
    delete clonedCabbage;
}

void testCabbageIsAlive() {
    Cabbage cabbage(1.0, 2.0, 10.0);
    assert(cabbage.isAlive());
    cabbage.setEnergy(0.0);
    assert(!cabbage.isAlive());
}

void testCabbageShouldReproduce() {
    Cabbage cabbage(1.0, 2.0, cabbage.getMaxEnergy());
    assert(cabbage.shouldReproduce());
    cabbage.setEnergy(cabbage.getMaxEnergy() - 1.0);
    assert(!cabbage.shouldReproduce());
}

int main() {
    testCabbageCreation();
    testCabbageEnergy();
    testCabbageReproduction();
    testCabbageClone();
    testCabbageIsAlive();
    testCabbageShouldReproduce();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
