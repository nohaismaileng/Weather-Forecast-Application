#ifndef RAPIDJSON_H
#define RAPIDJSON_H

#include "RapidjsonAbstract.h"


class Rapidjson : public RapidjsonAbstract
{
public:

    Rapidjson(char* response);

    std::string GetData() override;
    std::string GetTime() override;

    float GetTemp() override;
    float GetHumidity() override;
    float GetWindSpeed() override;

    int GetWeatherCode() override;
    float* GetMinForecastTemp() override;
    float* GetMaxForecastTemp() override;

    std::string* GetForecastDate() override;

    ~Rapidjson() override;
};

#endif