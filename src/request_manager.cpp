#include "request_manager.h"

namespace request_manager {
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    //==================================================================================
    void formCurlRequest(CURL* curl, const std::string& url, std::string& readBuffer) {
        struct curl_slist *hs=NULL;
        const std::string content_type = "Content-Type: application/json";
        hs = curl_slist_append(hs, content_type.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    }

    void formPostRequest(CURL* curl, const std::string& postthis) {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postthis.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)(postthis.size()));
    }

    void addAuthentificationHeader(CURL* curl, const std::string& token) {
        const std::string auth_str = "Authorization: Bearer " + token;
        struct curl_slist *hs1=NULL;
        hs1 = curl_slist_append(hs1, auth_str.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs1);
    }

    //=====================================================================================
    /*template <typename Fn> 
      std::string executeCurl(Fn&& fn) {
      CURL *curl;
      curl = curl_easy_init();
      std::string readBuffer;
      if(curl) {
      fn(curl, readBuffer);
    // Perform the request, res will get the return code
    auto res = curl_easy_perform(curl);
    // Check for errors
    if(res != CURLE_OK) {
    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }
    // always cleanup
    curl_easy_cleanup(curl);
    }
    return readBuffer;
    }*/

    //====================================================================================
    std::string getGetRequest(const std::string& url) {
        auto postreq = [&url](CURL* curl, std::string& buffer) {
            formCurlRequest(curl, url, buffer);
        };
        return executeCurl(postreq);
    }

    std::string getPostRequest(const std::string& url, const std::string& postthis) {
        auto postreq = [&url, &postthis](CURL* curl, std::string& buffer) {
            formCurlRequest(curl, url, buffer);
            formPostRequest(curl, postthis);
        };
        return executeCurl(postreq);
    }

    std::string getAuthentificationRequest(const std::string& url, const std::string& token) {
        auto postreq = [&url, &token](CURL* curl, std::string& buffer) {
            formCurlRequest(curl, url, buffer);
            addAuthentificationHeader(curl, token);
        };
        return executeCurl(postreq);
    }

    std::string getAuthentificationPostRequest(const std::string& url, const std::string& token, const std::string& postthis) {
        auto postreq = [&url, &token, &postthis](CURL* curl, std::string& buffer) {
            formCurlRequest(curl, url, buffer);
            formPostRequest(curl, postthis);
            addAuthentificationHeader(curl, token);
        };
        return executeCurl(postreq);
    }
}
