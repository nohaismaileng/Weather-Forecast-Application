#include "Rapidjson.h"

#include <string>


Rapidjson::Rapidjson(char* response)
{
    
    if (response == nullptr)
    {
        d.SetNull();
        return;
    }

    d.Parse(response);
}


std::string Rapidjson::GetData()
{

    if (d.HasParseError() || !d.IsObject())
    {
        return "";
    }

    if (!d.HasMember("current") ||
        !d["current"].IsObject())
    {
        return "";
    }

    const rapidjson::Value& current = d["current"];

    if (!current.HasMember("time") ||
        !current["time"].IsString())
    {
        return "";
    }

    std::string time = current["time"].GetString();

    if (time.length() >= 10)
    {
        return time.substr(0, 10);
    }

    return time;
}



std::string Rapidjson::GetTime()
{
    if (d.HasParseError() || !d.IsObject())
    {
        return "";
    }

    if (!d.HasMember("current") ||
        !d["current"].IsObject())
    {
        return "";
    }

    const rapidjson::Value& current = d["current"];

    if (!current.HasMember("time") ||
        !current["time"].IsString())
    {
        return "";
    }

    std::string time = current["time"].GetString();

    if (time.length() >= 16)
    {
        return time.substr(11, 5);
    }

    return time;
}


float Rapidjson::GetTemp()
{
    if (d.HasParseError() || !d.IsObject())
    {
        return 0.0f;
    }

    if (!d.HasMember("current") ||
        !d["current"].IsObject())
    {
        return 0.0f;
    }

    const rapidjson::Value& current = d["current"];

    if (!current.HasMember("temperature_2m") ||
        !current["temperature_2m"].IsNumber())
    {
        return 0.0f;
    }

    return current["temperature_2m"].GetFloat();
}



float Rapidjson::GetHumidity()
{
    if (d.HasParseError() || !d.IsObject())
    {
        return 0.0f;
    }

    if (!d.HasMember("current") ||
        !d["current"].IsObject())
    {
        return 0.0f;
    }

    const rapidjson::Value& current = d["current"];

    if (!current.HasMember("relative_humidity_2m") ||
        !current["relative_humidity_2m"].IsNumber())
    {
        return 0.0f;
    }

    return current["relative_humidity_2m"].GetFloat();
}



float Rapidjson::GetWindSpeed()
{
    if (d.HasParseError() || !d.IsObject())
    {
        return 0.0f;
    }

    if (!d.HasMember("current") ||
        !d["current"].IsObject())
    {
        return 0.0f;
    }

    const rapidjson::Value& current = d["current"];

    if (!current.HasMember("wind_speed_10m") ||
        !current["wind_speed_10m"].IsNumber())
    {
        return 0.0f;
    }

    return current["wind_speed_10m"].GetFloat();
}


int Rapidjson::GetWeatherCode()
{
    if (d.HasParseError() || !d.IsObject())
    {
        return 0;
    }

    if (!d.HasMember("current") ||
        !d["current"].IsObject())
    {
        return 0;
    }


    const rapidjson::Value& current = d["current"];

    if (!current.HasMember("weather_code") ||
        !current["weather_code"].IsInt())
    {
        return 0;
    }

    return current["weather_code"].GetInt();
}


float* Rapidjson::GetMinForecastTemp()
{

    static float minTemp[7] = {0};

    for (int i = 0; i < 7; i++)
    {
        minTemp[i] = 0.0f;
    }

    if (d.HasParseError() || !d.IsObject())
    {
        return minTemp;
    }

    if (!d.HasMember("daily") ||
        !d["daily"].IsObject())
    {
        return minTemp;
    }

    const rapidjson::Value& daily = d["daily"];

    if (!daily.HasMember("temperature_2m_min") ||
        !daily["temperature_2m_min"].IsArray())
    {
        return minTemp;
    }


    const rapidjson::Value& temperatures =
        daily["temperature_2m_min"];


    for (rapidjson::SizeType i = 0;
         i < temperatures.Size() && i < 7;
         i++)
    {
        if (temperatures[i].IsNumber())
        {
            minTemp[i] = temperatures[i].GetFloat();
        }
    }


    return minTemp;
}


float* Rapidjson::GetMaxForecastTemp()
{
    static float maxTemp[7] = {0};

    for (int i = 0; i < 7; i++)
    {
        maxTemp[i] = 0.0f;
    }


    if (d.HasParseError() || !d.IsObject())
    {
        return maxTemp;
    }


    if (!d.HasMember("daily") ||
        !d["daily"].IsObject())
    {
        return maxTemp;
    }


    const rapidjson::Value& daily = d["daily"];

    if (!daily.HasMember("temperature_2m_max") ||
        !daily["temperature_2m_max"].IsArray())
    {
        return maxTemp;
    }


    const rapidjson::Value& temperatures =
        daily["temperature_2m_max"];

    for (rapidjson::SizeType i = 0;
         i < temperatures.Size() && i < 7;
         i++)
    {
        if (temperatures[i].IsNumber())
        {
            maxTemp[i] = temperatures[i].GetFloat();
        }
    }


    return maxTemp;
}


std::string* Rapidjson::GetForecastDate()
{
 

    static std::string dates[7];

    for (int i = 0; i < 7; i++)
    {
        dates[i] = "";
    }


    if (d.HasParseError() || !d.IsObject())
    {
        return dates;
    }

    if (!d.HasMember("daily") ||
        !d["daily"].IsObject())
    {
        return dates;
    }


    const rapidjson::Value& daily = d["daily"];


    if (!daily.HasMember("time") ||
        !daily["time"].IsArray())
    {
        return dates;
    }


    const rapidjson::Value& forecastDates =
        daily["time"];


    for (rapidjson::SizeType i = 0;
         i < forecastDates.Size() && i < 7;
         i++)
    {
        if (forecastDates[i].IsString())
        {
            dates[i] = forecastDates[i].GetString();
        }
    }


    return dates;
}


Rapidjson::~Rapidjson()
{
}