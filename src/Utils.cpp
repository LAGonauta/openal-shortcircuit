#include "Utils.hpp"

DLL_LOCAL std::string string_join(const std::vector<std::string>& strings, const char separator)
{
    std::string ret;
    
    for (auto it = strings.begin(); it != strings.end(); ++it)
        {
        ret += *it;
        if (it != strings.end() - 1)
        {
            ret += separator;
        }
    }

    return ret;
}

DLL_LOCAL std::vector<std::string> string_unwrap(const char* oal_strings, const std::string separator)
{
    std::vector<std::string> ret;

    if(!oal_strings || *oal_strings == '\0')
    {
        return ret;
    }

    std::string string = std::string(oal_strings);
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(separator)) != std::string::npos)
    {
        token = string.substr(0, pos);
        ret.push_back(token);
        string.erase(0, pos + separator.length());
    }

    return ret;
}
