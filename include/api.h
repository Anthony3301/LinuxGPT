// class to access the open ai api
#include <cstddef>
#include <string>

class API {
    std::string httpRequest;

    // utility function to call api
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    public:
        // ctor
        API();

        // dtor
        ~API();

        // access point
        void access();
};