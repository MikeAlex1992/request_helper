#pragma once

#include <curl/curl.h>
#include <string>
#include <cstring>
#include <iostream>

namespace request_manager {
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

    //==================================================================================
    void formCurlRequest(CURL* curl, const std::string& url, std::string& readBuffer);
    void formPostRequest(CURL* curl, const std::string& postthis);
    void addAuthentificationHeader(CURL* curl, const std::string& token);

    //=====================================================================================
    template <typename Fn> 
        std::string executeCurl(Fn&& fn) {
            CURL *curl;
            curl = curl_easy_init();
            std::string readBuffer;
            if(curl) {
                fn(curl, readBuffer);
                /* Perform the request, res will get the return code */
                auto res = curl_easy_perform(curl);
                /* Check for errors */
                if(res != CURLE_OK) {
                    std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
                }
                /* always cleanup */
                curl_easy_cleanup(curl);
            }
            return readBuffer;
        }

    //====================================================================================
    std::string getGetRequest(const std::string& url);
    std::string getPostRequest(const std::string& url, const std::string& postthis);
    std::string getAuthentificationRequest(const std::string& url, const std::string& token);
    std::string getAuthentificationPostRequest(const std::string& url, const std::string& token, const std::string& postthis);
}
