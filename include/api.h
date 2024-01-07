// class to access the open ai api
#include <cstddef>
#include <string>

class API {
    std::string httpRequest;
    std::string response;

    // utility function to call api
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    std::string normalizeString(const std::string& input);

    public:
        // ctor
        API();

        // dtor
        ~API();

        // access point
        void access(std::string apiKey, std::string prompt);

        // get the response string from the json
        std::string parseResult();


        // setters and getters
        void setHttpsRequest(const std::string &s);
};