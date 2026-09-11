#ifndef CITIES_H
#define CITIES_H

#include <map>
#include <string>
#include <utility>
#include <vector>

class Cities
{
private:
    std::map<std::string, std::pair<std::string, std::string>> cities;

public:
    void AddCity(
        const std::string& name,
        const std::string& latitude,
        const std::string& longitude
    );

    std::pair<std::string, std::string> GetAxis(
        const std::string& name
    ) const;
    std::vector<std::string> GetCities() const;
};

#endif