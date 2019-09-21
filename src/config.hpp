#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <regex> // C++11
#include <filesystem> // C++17: exists

namespace fs = std::filesystem;

/**
 * The configuration class holds all information regarding
 * to the list of domains that shall be analyzed.
 */
class Config {
    std::string file_path_;
    std::vector<std::string> domains_;

    void init();
public:
    /**
     * Initializes the configuration with a given file path.
     * This file path can be absolute or relative to the
     * current working directory.
     *
     * @param file_path: absolute or relative path to a text
     *                   file with a list of domains
     *                   (line by line)
     */
    Config(std::string file_path) : file_path_{file_path}
    {}

    /**
     * Parses the config. Each line in the config contains
     * a domain. The HTTPS certificates will be fetched and
     * interpreted.
     *
     * @return Parsing was successful (true) or not (false).
     */
    bool parse();

    /**
     * Checks whether the given file path for the configuration
     * exists.
     * 
     * @return true if file exists, false if not.
     */
    bool file_exists() {
        return fs::exists(file_path_);
    }

    /**
     * Getter method for domains list of configuration file
     *
     * @return vector of domains as strings
     */
    std::vector<std::string> get_domains()
    {
        return domains_;
    }
};
