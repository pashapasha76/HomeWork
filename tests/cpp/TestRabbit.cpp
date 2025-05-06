#include <cassert>
#include "Rabbit.h"
#include "Area.h"

void testRabbitCreation() {
    Rabbit rabbit(1.0, 2.0, 30.0);
    assert(rabbit.getX() == 1.0);
    assert(rabbit.getY() == 2.0);
    assert(rabbit.getEnergy() == 30.0);
    assert(rabbit.getId() == 0); // Assuming no other objects have been created
}

void testRabbitEnergy() {
    Rabbit rabbit(1.0, 2.0, 30.0);
    rabbit.setEnergy(40.0);
    assert(rabbit.getEnergy() == 40.0);
    rabbit.setEnergy(60.0);
    assert(rabbit.getEnergy() == rabbit.getMaxEnergy());
}

void testRabbitReproduction() {
    Rabbit rabbit(1.0, 2.0, rabbit.getMaxEnergy());
    Creature* newRabbit = rabbit.reproduce();
    assert(newRabbit != nullptr);
    assert(newRabbit->getEnergy() == rabbit.getMaxEnergy() / 2);
    assert(rabbit.getEnergy() == rabbit.getMaxEnergy() / 2);
    delete newRabbit;
}

void testRabbitMovement() {
    Rabbit rabbit(1.0, 2.0, 50.0);
    double initialEnergy = rabbit.getEnergy();
    rabbit.move(4.0, 6.0, 100.0, 100.0);
    assert(rabbit.getX() == 4.0);
    assert(rabbit.getY() == 6.0);
    assert(rabbit.getEnergy() == initialEnergy - rabbit.getEnergyCostPerUnit() * 5);
}

void testRabbitClone() {
    Rabbit rabbit(1.0, 2.0, 30.0);
    Creature* clonedRabbit = rabbit.clone();
    assert(clonedRabbit != nullptr);
    assert(clonedRabbit->getX() == rabbit.getX());
    assert(clonedRabbit->getY() == rabbit.getY());
    assert(clonedRabbit->getEnergy() == rabbit.getEnergy());
    delete clonedRabbit;
}

void testRabbitIsAlive() {
    Rabbit rabbit(1.0, 2.0, 30.0);
    assert(rabbit.isAlive());
    rabbit.setEnergy(0.0);
    assert(!rabbit.isAlive());
}

void testRabbitShouldReproduce() {
    Rabbit rabbit(1.0, 2.0, rabbit.getMaxEnergy());
    assert(rabbit.shouldReproduce());
    rabbit.setEnergy(rabbit.getMaxEnergy() - 1.0);
    assert(!rabbit.shouldReproduce());
}

int main() {
    testRabbitCreation();
    testRabbitEnergy();
    testRabbitReproduction();
    testRabbitMovement();
    testRabbitClone();
    testRabbitIsAlive();
    testRabbitShouldReproduce();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
