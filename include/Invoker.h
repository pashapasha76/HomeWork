#ifndef INVOKER_H
#define INVOKER_H

#include <vector>
#include "Command.h"

class Invoker {
private:
    std::vector<Command*> commands;
public:
    void addCommand(Command* command);
    void executeCommands();
};

#endif 
