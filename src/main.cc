#include <iostream>
#include "logger.h"
#include "controller.h"
#include "directory.h"
#include "api.h"
#include <limits>
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

    // create the API object
    API api;

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

    while(true) {
        logger.info("Enter your prompt on a single line or exit:");
        
        
        if (!std::getline(cin, command) || command == "exit") {
            break;
        }

        controller.setPastRequest(command);
        directory.getTreeDirectory(MAX_DEPTH);

        // do api access here
        api.setHttpsRequest(controller.getHttpsRequestString());
        api.access(controller.getApiKey(), controller.getFinalRequestString());
        std::string result = api.parseResult();

        // display command to users
        std::istringstream iss{result};
        std::string currLine;

        int counter = 0;
        while(std::getline(iss, currLine)) {
            if (counter != -1) {
                logger.info(std::to_string(counter) + ": " + currLine);

                // check if the command has any potentially dangerous commands in it
                if (directory.isOkCommand(currLine) == commandSafety::DANGER) {
                    logger.warning("This command contains a potentially dangerous action!");
                }

                // prompt user to see to run command or not
                std::string usrInput;
                logger.info("Run command ? (y/n):");
                std::cin >> usrInput;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                while (true) {

                    if (usrInput == "y" || usrInput == "Y" || usrInput == "yes" || usrInput == "Yes" || usrInput == "YES") {
                        logger.info("Running command...");
                        directory.runCommand(currLine);
                        logger.info("Success");
                        break;
                    } else if (usrInput == "n" || usrInput == "N" || usrInput == "no" || usrInput == "No" || usrInput == "NO") {
                        logger.info("Skipping command");
                        break;
                    } else {
                        logger.error("Urecognized command, input again (y/n)");
                    }
                }

            }
            counter++;
        }

        logger.info("All commands complete.");
    }
}