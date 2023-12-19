#include "controller.h"
#include "logger.h"
#include "directory.h"
#include <fstream>

// basic ctor
Controller::Controller(std::string fp): configFilePath{fp} {}

// reads api key from config file
fileState Controller::getAPIkey() {
    // config file where the api key is stored
    std::ifstream configFile(configFilePath);

    
    if (configFile.is_open()) {
        std::string key;

        if (std::getline(configFile, key)) {
            this->setApiKey(key);
            return fileState::SUCCESS;
        } else {
            return fileState::NOKEY;
        }

        configFile.close();
    } else { // unable to open file
        return fileState::NOFILE;
    }

    return fileState::NOFILE;
}


// writes api key to file
fileState Controller::writeAPIkey(std::string key) {
    // config file where the api key will be stored
    std::ofstream configFile(configFilePath);

    
    if (configFile.is_open()) {

        configFile << key << std::endl;
        return fileState::SUCCESS;
        
        configFile.close();
    } else { // unable to open file
        return fileState::NOFILE;
    }

    return fileState::NOFILE;;
}

// handles the reading/writing of api key from file
bool Controller::init() {
    std::string line;

    // attempt to get the api key
    fileState readOutcome = this->getAPIkey();

    // basic init
    if (readOutcome == fileState::SUCCESS) {
        logger.info("Successfully read API key from config.txt!");
        return true;
    } else if (readOutcome == fileState::NOKEY) {
        logger.warning("Could not read API key from config.txt.");
    } else {
        logger.error("Could not find config.txt.");
    }

    return false;
}


// method that creates the request string
std::string Controller::getFinalRequestString() {
    std::string tmp;

    tmp += "User request is:\n";
    tmp += pastRequest;
    tmp += "\nDirectory structure is:\n";

    // read from output.txt file and add the structure line by line
    std::ifstream tree("output.txt");
    std::string row;
    
    while (std::getline(tree, row)) {
        tmp += row + "\n";
    }

    return tmp;
}


// getters and setters
void Controller::setApiKey(std::string s) {apiKey = s;}


void Controller::setPastRequest(std::string s) {pastRequest = s;}
std::string Controller::getPastRequest() {return pastRequest;}

