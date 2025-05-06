#include "Invoker.h"
#include<iostream>

void Invoker::addCommand(Command* command) {
    commands.push_back(command);
    
}

void Invoker::executeCommands() {
    for (Command* command : commands) {
        command->execute();
        delete command;
    }
    commands.clear();
}
