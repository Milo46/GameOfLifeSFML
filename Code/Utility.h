#ifndef UTILITY_H
#define UTILITY_H

#include <fstream>

#include "jsonlib/json.hpp"

namespace Utility
{
    bool loadJsonFromFile(const std::string& filename, nlohmann::json& json_object);
}

#endif // UTILITY_H
