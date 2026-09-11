#include "Cities.h"

void Cities::AddCity(
    const std::string& name,
    const std::string& latitude,
    const std::string& longitude
)
{
    cities[name] = std::make_pair(latitude, longitude);
}

std::pair<std::string, std::string> Cities::GetAxis(
    const std::string& name
) const
{
    auto it = cities.find(name);

    // City doesn't exist
    if (it == cities.end())
    {
        return {"", ""};
    }

    return it->second;
}

std::vector<std::string> Cities::GetCities() const
{
    std::vector<std::string> result;

    result.reserve(cities.size());

    for (const auto& city : cities)
    {
        result.push_back(city.first);
    }

    return result;
}