#include "Command.h"
#include "Animal.h"
#include "Creature.h"
#include "Cabbage.h"
#include "Area.h"
#include <cmath>
#include <limits>
#include <iostream>


MoveCommand::MoveCommand(Animal* animal, double x, double y, double width, double height)
    : animal(animal), x(x), y(y), width(width), height(height) {}

void MoveCommand::execute() {
    if (animal->isAlive()) {
        animal->move(x, y, width, height);
        animal->print();
    }
}

EatCommand::EatCommand(Animal* predator, Creature* prey)
    : predator(predator), prey(prey) {}

void EatCommand::execute() {
    if (predator->isAlive() && prey->isAlive()) {
        predator->replenishEnergy(prey->getEnergy());
        prey->setEnergy(0);
    }
}

ReproduceCommand::ReproduceCommand(Creature* creature, std::vector<Creature*>& creatures)
    : creature(creature), creatures(creatures) {}

void ReproduceCommand::execute() {
    if (creature->isAlive()) {
        Creature* newCreature = creature->reproduce();
        creatures.push_back(newCreature);
    }
}

HuntCommand::HuntCommand(Animal* hunter, Area& area)
    : hunter(hunter), area(area) {}

void HuntCommand::execute() {
    if (hunter->isAlive()) {
        std::string preyName = hunter->getTarget();
        Creature* closestPrey = nullptr;
        double closestDistance = hunter->getViewRadius();
        for (Creature* creature : area.getCreatures()) {
            
            if (creature->getName() == preyName && creature->isAlive()) {
                
                double distance = hunter->distanceTo(*creature);
                
                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestPrey = creature;
                    
                    
                }
            }
        }
        
        if (closestPrey) {
            double dx = closestPrey->getX() - hunter->getX();
            double dy = closestPrey->getY() - hunter->getY();
            double distance = std::hypot(dx, dy);

            if (distance <= hunter->getCatchRadius()) {
                hunter->replenishEnergy(closestPrey->getEnergy() - distance * hunter->getEnergyCostPerUnit());
                closestPrey->setEnergy(0);
            } else {
                hunter->move(closestPrey->getX(), closestPrey->getY(), area.getWidth(), area.getHeight());            }
        } else {
            double newX = static_cast<double>(rand()) / RAND_MAX * hunter->getCatchRadius() / 2;
            double newY = static_cast<double>(rand()) / RAND_MAX * hunter->getCatchRadius() / 2;
            hunter->move(newX, newY, area.getWidth(), area.getHeight());
        }
    }
}

GrowCommand::GrowCommand(Cabbage* cabbage)
    : cabbage(cabbage){}

void GrowCommand::execute() {
    if (cabbage->isAlive()) {
        cabbage->replenishEnergy(cabbage->getGrowEnergy());
    }
}
