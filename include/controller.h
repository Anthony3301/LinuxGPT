#ifndef __CONTROLLER__H__
#define __CONTROLLER__H__

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

enum class fileState {
    SUCCESS,
    NOKEY,
    NOFILE
};

class Controller {
    std::string apiKey;
    std::string pastRequest;
    std::string configFilePath;

    public:
        Controller(std::string fp);

        // methods to read/write from config file
        fileState getAPIkey();
        fileState writeAPIkey(std::string s);

        // method that inits the api key from file
        bool init();

        ~Controller() {}

        // method that creates the request string
        std::string getFinalRequestString();

        // getters and setters
        void setApiKey(std::string s);
        
        void setPastRequest(std::string s);
        std::string getPastRequest();

};


#endif