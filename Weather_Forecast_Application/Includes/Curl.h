#ifndef CURL_H
#define CURL_H

#include "CurlAbstract.h"
#include "DataAbstract.h"

#include <string>

class Curl : public CurlAbstract
{
private:

    std::string latitude;
    std::string longitude;
    DataAbstract* data;

public:
    Curl(
        const std::string& latitude,
        const std::string& longitude,
        DataAbstract* data
    );

    CURLcode Curl_Init() override;

    CURLcode Curl_Setup() override;

    CURLcode Curl_Preform() override;

    ~Curl() override;
};

#endif