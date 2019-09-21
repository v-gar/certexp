#include "cert.hpp"

using std::string;
using std::vector;

void CertificateChain::init()
{
    for (string certificate : raw) {
        std::istringstream certifcate_instream{certificate};
        string line;
        
        vector<string> san_raw{};
        string expire_raw{};
        
        std::tm expire_time{};
        
        while (std::getline(certifcate_instream, line)) {            
            if (starts_with(line.c_str(), EXPIRE_DATE_HEADER))
                expire_raw = line.substr(strlen(EXPIRE_DATE_HEADER));
            
            if (starts_with(line.c_str(), SAN_HEADER)) {
                auto dns_string = line.substr(strlen(SAN_HEADER));
                
                std::stringstream ss{dns_string};
                std::string token;
                while (std::getline(ss, token, ',')) {
                    san_raw.push_back(token.substr(4)); // strlen("DNS:") == 4
                }
            }
        }
        
        // convert expire_raw to time
        {
            // workaround for GCC Bugzilla bugs #71556, #45896
            if (expire_raw[4] == ' ')
                expire_raw[4] = '0'; // fill with leading zero
            
            std::stringstream ss{expire_raw};
            ss >> std::get_time(&expire_time, "%b %d %H:%M:%S %Y GMT");
        }
        
        for (std::string san : san_raw) {
            certs.insert(
                std::make_pair<std::string, std::tm>(
                    string{san},
                    std::tm{expire_time}
                )
            );
        }        
    }
}
