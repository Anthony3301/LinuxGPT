#include "directory.h"

// ctor
Directory::Directory() {}


// dtor
Directory::~Directory() {}


// private method to run a command in terminal
int Directory::runCommand(std::string cm) {
    // need c-style string for this
    const char *command = cm.c_str();

    // validation will be run in the main control
    return std::system(command);
}



// checking if a linux command is potentiall destructive
commandSafety Directory::isOkCommand(std::string cm) {
    for (auto danger: dangerousCommands) {
        if (cm.find(danger) != std::string::npos) { // potentially dangerous command
            return commandSafety::DANGER;
        }
    }

    return commandSafety::SAFE;
}


// pipes the string output of the directory to file output.txt
int Directory::getTreeDirectory(size_t depth) {
    std::string treeCmd = "tree -L " + std::to_string(depth) + " > output.txt";
    return this->runCommand(treeCmd);
}