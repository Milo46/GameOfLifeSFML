#include "Utility.h"

namespace Utility
{
    bool loadJsonFromFile(const std::string& filename, nlohmann::json& json_object)
    {
        std::fstream file(filename, std::ios_base::in);
        if (file.is_open())
        {
            try
            {
                file >> json_object;
            }
            catch(...)
            {
                return false;
            }
        }
        else
        {
            return false;
        }
        file.close();
        return true;
    }
}
