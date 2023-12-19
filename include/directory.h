#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

enum class commandSafety {SAFE, DANGER};

// utility class for running terminal commands
class Directory {
    std::vector<std::string> dangerousCommands {
        "rm -rf", "dd", "mkfs.ext4", "chmod -R 77", "sudo"
    };


    public:
        Directory() {}

        ~Directory() {}

        commandSafety isOkCommand(std::string cm) {
            for (auto danger: dangerousCommands) {
                if (cm.find(danger) != std::string::npos) { // potentially dangerous command
                    return commandSafety::DANGER;
                }
            }

            return commandSafety::SAFE;
        }

        int getTreeDirectory() {
            const char *command = "tree > output.txt";

            return std::system(command);
        }

        int runCommand(std::string cm) {
            // need c-style string for this
            const char *command = cm.c_str();

            // validation will be run in the main control
            return std::system(command);
        }
};

#endif