#include <cassert>
#include "Wolf.h"
#include "Area.h"

void testWolfCreation() {
    Wolf wolf(1.0, 2.0, 50.0, 0.5);
    assert(wolf.getX() == 1.0);
    assert(wolf.getY() == 2.0);
    assert(wolf.getEnergy() == 50.0);
    assert(wolf.getId() == 0);
}

void testWolfEnergy() {
    Wolf wolf(1.0, 2.0, 50.0, 0.5);
    wolf.setEnergy(75.0);
    assert(wolf.getEnergy() == 75.0);
    wolf.setEnergy(120.0);
    assert(wolf.getEnergy() == wolf.getMaxEnergy());
}

void testWolfReproduction() {
    Wolf wolf(1.0, 2.0, wolf.getMaxEnergy(), 0.5);
    Creature* newWolf = wolf.reproduce();
    assert(newWolf != nullptr);
    assert(newWolf->getEnergy() == wolf.getMaxEnergy() / 2);
    assert(wolf.getEnergy() == wolf.getMaxEnergy() / 2);
    delete newWolf;
}

void testWolfMovement() {
    Wolf wolf(1.0, 2.0, 50.0, 0.5);
    double initialEnergy = wolf.getEnergy();
    wolf.move(3.0, 4.0, 10.0, 10.0);
    assert(wolf.getX() == 3.0);
    assert(wolf.getY() == 4.0);
}

void testWolfClone() {
    Wolf wolf(1.0, 2.0, 50.0, 0.5);
    Creature* clonedWolf = wolf.clone();
    assert(clonedWolf != nullptr);
    assert(clonedWolf->getX() == wolf.getX());
    assert(clonedWolf->getY() == wolf.getY());
    assert(clonedWolf->getEnergy() == wolf.getEnergy());
    delete clonedWolf;
}

void testWolfIsAlive() {
    Wolf wolf(1.0, 2.0, 50.0, 0.5);
    assert(wolf.isAlive());
    wolf.setEnergy(0.0);
    assert(!wolf.isAlive());
}

void testWolfShouldReproduce() {
    Wolf wolf(1.0, 2.0, wolf.getMaxEnergy(), 0.5);
    assert(wolf.shouldReproduce());
    wolf.setEnergy(wolf.getMaxEnergy() - 1.0);
    assert(!wolf.shouldReproduce());
}

void testWolfWillHunt() {
    Wolf wolf(1.0, 2.0, 50.0, 1.0);
    assert(wolf.willHunt());
    Wolf peacefulWolf(1.0, 2.0, 50.0, 0.0);
    assert(!peacefulWolf.willHunt());
}

int main() {
    testWolfCreation();
    testWolfEnergy();
    testWolfReproduction();
    testWolfMovement();
    testWolfClone();
    testWolfIsAlive();
    testWolfShouldReproduce();
    testWolfWillHunt();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
