#ifndef _CERT_H
#define _CERT_H

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

#include <cstring>
#include <ctime>
#include <iostream>
#include <iomanip>

#include "net.hpp"

static const char *EXPIRE_DATE_HEADER = "Expire date:";
static const char *SAN_HEADER = "X509v3 Subject Alternative Name:";

class CertificateChain {
    /**
     * Vector with raw certificate data
     * (line by line)
     */
    std::vector<std::string> raw;
    
    /**
     * Unordered map with the certifcate data.
     * Certificates can contain multiple
     * SAN (Subject Alternative Names) but one
     * expiry date. This map contains the
     * (same) expiry date for every SAN entry
     * so an expiry date can be easily looked up
     * by an SAN.
     */
    std::unordered_map<std::string, std::tm> certs;
    
    void init();
    
public:
    CertificateChain(struct fetch_result fetch_result)
    : raw{fetch_result.cert_data}
    {
        init();
    }
    
    std::unordered_map<std::string, std::tm> get_certs()
    {
        return certs;
    }
};

static bool starts_with(const char *a, const char *b)
{
    if (strncmp(a, b, strlen(b)) == 0)
        return true;
    return false;
}

#endif
