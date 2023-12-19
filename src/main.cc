#include <iostream>
#include "logger.h"
#include "controller.h"
#include "directory.h"
using namespace std;

// global logger
Logger logger("output.log");

const size_t MAX_DEPTH = 10;

int main() {
    logger.info("Welcome to linuxGPT");

    // create the controller object
    Controller controller("config.txt");

    // create the directory object
    Directory directory;

    // initalization loop
    while (true) {
        if (controller.init()) {
            break; // successfully found the api key and loaded it
        }

        logger.info("Enter API key:");
        std::string key;
        cin >> key;

        // write the key and let the loop run again
        controller.writeAPIkey(key);
    }

    std::string command;
    logger.info("Enter your prompt on a single line:");

    while(std::getline(cin, command)) {
        controller.setPastRequest(command);
        directory.getTreeDirectory(MAX_DEPTH);
        logger.info(controller.getFinalRequestString());

        // do api access here
    }
}