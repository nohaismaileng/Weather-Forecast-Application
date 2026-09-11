#include "Curl.h"
#include "Data.h"

#include <curl/curl.h>


Curl::Curl(
    const std::string& latitude,
    const std::string& longitude,
    DataAbstract* data
)
    : latitude(latitude),
      longitude(longitude),
      data(data)
{

    weatherAPI =
        "https://api.open-meteo.com/v1/forecast"
        "?latitude=" + latitude +
        "&longitude=" + longitude +
        "&current=temperature_2m,relative_humidity_2m,wind_speed_10m,weather_code"
        "&daily=temperature_2m_max,temperature_2m_min,weather_code"
        "&forecast_days=7"
        "&timezone=auto";
}


CURLcode Curl::Curl_Init()
{
    curl = curl_easy_init();

    if (curl == nullptr)
    {
        result = CURLE_FAILED_INIT;
        return result;
    }

    result = CURLE_OK;

    return result;
}


CURLcode Curl::Curl_Setup()
{

    if (curl == nullptr)
    {
        result = CURLE_FAILED_INIT;
        return result;
    }

    if (data == nullptr)
    {
        result = CURLE_FAILED_INIT;
        return result;
    }


    data->Clear();

    curl_easy_setopt(
        curl,
        CURLOPT_URL,
        weatherAPI.c_str()
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEFUNCTION,
        &Data::write_chunk
    );

    curl_easy_setopt(
        curl,
        CURLOPT_WRITEDATA,
        data
    );

    curl_easy_setopt(
        curl,
        CURLOPT_FOLLOWLOCATION,
        1L
    );

    curl_easy_setopt(
        curl,
        CURLOPT_CONNECTTIMEOUT,
        10L
    );


    curl_easy_setopt(
        curl,
        CURLOPT_TIMEOUT,
        20L
    );

    curl_easy_setopt(
        curl,
        CURLOPT_USERAGENT,
        "WeatherForecastApplication/1.0"
    );


    curl_easy_setopt(
        curl,
        CURLOPT_SSL_VERIFYPEER,
        1L
    );


    curl_easy_setopt(
        curl,
        CURLOPT_SSL_VERIFYHOST,
        2L
    );


    result = CURLE_OK;

    return result;
}

CURLcode Curl::Curl_Preform()
{
    if (curl == nullptr)
    {
        result = CURLE_FAILED_INIT;
        return result;
    }


    result = curl_easy_perform(curl);


    return result;
}


Curl::~Curl()
{
    if (curl != nullptr)
    {
        curl_easy_cleanup(curl);
        curl = nullptr;
    }
}