#include "api.h"

#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "logger.h"

// ctor
API::API(): httpRequest{"https://platform.openai.com"} {} // temporary

// dtor
API::~API() {}


// utility function
size_t API::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// utility function to normalize string for json (to deal with additional newlines inside input)
std::string API::normalizeString(const std::string& input) {
    std::string result;
    for (char c : input) {
        switch (c) {
            case '\n':
                result += "\\n";
                break;
            // Add more cases if needed
            default:
                result += c;
        }
    }
    return result;
}


// access point
void API::access(std::string apiKey, std::string prompt) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/chat/completions");

        // Set the headers
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string auth = "Authorization: Bearer " + apiKey;
        headers = curl_slist_append(headers, auth.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // Set the POST data
        std::string postData = "{ \"model\": \"gpt-4\", \"messages\": [ { \"role\": \"system\", \"content\": \"You are an assistant for Linux commands, you just provide the code snippet, no other output, do not wrap the code in markdown formatter, if request does not make sense, output FAIL\" }, { \"role\": \"user\", \"content\": \"(input_here)\" } ] }";
        size_t startPromptPos = postData.find("(input_here)");
        if (startPromptPos != std::string::npos) {
            std::string normalizedInput = normalizeString(prompt);
            postData.replace(startPromptPos, 12, normalizedInput);
        }

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());

        // Set the callback function for writing the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // Perform the request
        res = curl_easy_perform(curl);

        // Cleanup
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        // Output the response
        if (res == CURLE_OK && readBuffer.find("FAIL") == std::string::npos) {
            //std::cout << readBuffer << std::endl;

            // store the response string
            response = readBuffer;
            logger.info("Success");
        } else {
            logger.error("Request Failed");
        }
    }

    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }
}

std::string API::parseResult() {
    // parse the string into a json object
    try {
        nlohmann::json jsonString = nlohmann::json::parse(this->response);

        //std::cout << jsonString << std::endl;

        // need the content which is under choices->message->content (just choose first response for now)
        std::string res = jsonString["choices"][0]["message"]["content"];

        // content sometimes comes with ```bash at the front and ``` at the end, need the content between the two

        // find the ```bash first
        size_t startPos = res.find("```bash");

        if (startPos != std::string::npos) {
            // find the ``` after the first occurence
            size_t endPos = res.find("```", startPos + 7);

            // substring between these two is the needed result
            res = res.substr(startPos+7, endPos - startPos - 6);
        } // otherwise just keep the stuff as needed
    
        //logger.warning(res);

        return res;
    } catch (std::exception &ex) {
        std::cout << ex.what() << std::endl;
        logger.error("Error when parsing result");
        return "";
    }
}


// setter
void API::setHttpsRequest(const std::string &s) {
    this->httpRequest = s;
}