#ifndef _NET_H
#define _NET_H

#include <string>
#include <sstream>
#include <vector>
#include <memory>

#include <cstring>

#include <curl/curl.h>

/**
 * Container of fetch results being returned
 * by the fetch function.
 */
struct fetch_result {
    /**
     * Boolean whether fetching was successful.
     */
    bool success;
    
    /**
     * Vector with raw certificate data
     * (line by line)
     */
    std::vector<std::string> cert_data;
    
    /**
     * Constructor initializing the success
     * bool variable with false.
     */
    fetch_result() : success{false}
    {}
};

/**
 * Function fetching the certifcate by creating
 * an HTTPS connection to the server and grabbing
 * the certificate information.
 *
 * @param domain: domain name (e.g. example.com) to analyse
 * @return a struct fetch_result with the corresponding
 * information
 */
struct fetch_result fetch(std::string domain);

/**
 * Converts a hostname string to an HTTPS url
 * with the const char * type.
 *
 * @param domain: domain to be called (e.g. example.com)
 * @returns URL (e.g. https://example.com/)
 */
const char *convert_hostname_to_url(std::string domain);

static size_t write_function(void *ptr, size_t size,
                             size_t nmemb, void *stream)
{
    (void)stream;
    (void)ptr;
    return size * nmemb;
}

#endif
