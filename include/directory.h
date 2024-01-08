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
        "rm -rf", "dd", "mkfs.ext4", "chmod -R 77", "sudo", ":(){:|:&};:", "> /dev/sda", 
        "/dev/null", "wget", "mkfs.ext3", "crontab -r", "<em>" 
    };


    public:
        // ctor
        Directory();

        // dtor
        ~Directory();

        // checks if a command is potentially dangerous
        commandSafety isOkCommand(std::string cm);

        // gets the directory structure (up to a specific depth)
        int getTreeDirectory(size_t depth);

        int runCommand(std::string cm);
};

#endif