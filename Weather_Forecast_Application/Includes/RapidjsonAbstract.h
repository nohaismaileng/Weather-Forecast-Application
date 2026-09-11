#ifndef RAPIDJSONABSTRACT_H
#define RAPIDJSONABSTRACT_H

#include <string>

#include "rapidjson/document.h"


class RapidjsonAbstract
{
protected:

    rapidjson::Document d;

public:

    virtual std::string GetData() = 0;
    virtual std::string GetTime() = 0;
    virtual float GetTemp() = 0;
    virtual float GetHumidity() = 0;
    virtual float GetWindSpeed() = 0;
    virtual int GetWeatherCode() = 0;
    virtual float* GetMinForecastTemp() = 0;
    virtual float* GetMaxForecastTemp() = 0;
    virtual std::string* GetForecastDate() = 0;
    virtual ~RapidjsonAbstract();
};

#endif