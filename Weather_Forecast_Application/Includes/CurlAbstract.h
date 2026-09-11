#ifndef CURLABSTRACT_H
#define CURLABSTRACT_H

#include <curl/curl.h>
#include <string>

class CurlAbstract
{
protected:
    CURL* curl;
    CURLcode result;
    std::string weatherAPI;

public:
    CurlAbstract();
    virtual CURLcode Curl_Init() = 0;
    virtual CURLcode Curl_Setup() = 0;
    virtual CURLcode Curl_Preform() = 0;
    virtual ~CurlAbstract();
};

#endif