#include "config.hpp"
#include "constants.hpp"

bool Config::parse()
{
    if (!file_exists())
        return false;
    
    std::ifstream in{file_path_};
    
    if (!in.is_open())
        return false;
    
    // prepare regex
    std::regex domain_regex(DOMAIN_REGEX);
    
    std::string line;
    while (std::getline(in, line)) {
        if (std::regex_match(line, domain_regex))
            domains_.push_back(line);
        else
            std::cerr << "Error: " 
                      << line << " is not a valid hostname FQDN." 
                      << std::endl;
    }

    return true;
}
