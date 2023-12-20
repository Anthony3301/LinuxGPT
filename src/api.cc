#include "api.h"

#include <iostream>
#include <string>
#include <curl/curl.h>

// ctor
API::API(): httpRequest{"https://platform.openai.com"} {} // temporary

// dtor
API::~API() {}


// utility function
size_t API::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


// access point
void API::access() {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, httpRequest.c_str()); // needed for some reason on g++
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

            std::cout << readBuffer << std::endl;
    }
}