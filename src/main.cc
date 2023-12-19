#include <iostream>
#include "logger.h"
#include "controller.h"
using namespace std;

// global logger
Logger logger("output.log");

int main() {
    logger.info("Welcome to linuxGPT");

    // create the controller object
    Controller controller("config.txt");

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
}