#ifndef COMMAND_H
#define COMMAND_H

#include <vector>

class Animal;
class Creature;
class Area;
class Cabbage;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

class MoveCommand : public Command {
private:
    Animal* animal;
    double x, y;
    double width, height;
public:
    MoveCommand(Animal* animal, double x, double y, double width, double height);
    void execute() override;
};

class EatCommand : public Command {
private:
    Animal* predator;
    Creature* prey;
public:
    EatCommand(Animal* predator, Creature* prey);
    void execute() override;
};

class ReproduceCommand : public Command {
private:
    Creature* creature;
    std::vector<Creature*>& creatures;
public:
    ReproduceCommand(Creature* creature, std::vector<Creature*>& creatures);
    void execute() override;
};

class HuntCommand : public Command {
private:
    Animal* hunter;
    Area& area;
public:
    HuntCommand(Animal* hunter, Area& area);
    void execute() override;
};

class GrowCommand : public Command {
private:
    Cabbage* cabbage;
public:
    GrowCommand(Cabbage* cabbage);
    void execute() override;
};

#endif 
