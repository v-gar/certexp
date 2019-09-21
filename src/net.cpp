#include "net.hpp"

using std::string;

struct fetch_result fetch(string domain)
{
    struct fetch_result result{};

    // License notice: this code was adapted
    // from https://curl.haxx.se/libcurl/c/certinfo.html
    // 
    // The license can be found unter COPYING_CURL

    // curl init
    CURL *curl;
    CURLcode res;
    
    curl_global_init(CURL_GLOBAL_DEFAULT);
    
    curl = curl_easy_init();
    
    if (curl) {
        char *url = convert_hostname_to_url(domain); // pointer owner!
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_function);
 
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
 
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 0L);
        curl_easy_setopt(curl, CURLOPT_CERTINFO, 1L);
 
        // request
        res = curl_easy_perform(curl);

        if (!res) {
            // if successful: get certificate data
            struct curl_certinfo *certinfo;
 
            res = curl_easy_getinfo(curl, CURLINFO_CERTINFO, &certinfo);

            if(!res && certinfo) {
                int i;
                
                std::vector<std::string> cert_data{};
                
                // the certificate data is present as a big string
                for(i = 0; i < certinfo->num_of_certs; i++) {
                    std::stringstream ss;
                    
                    struct curl_slist *slist;

                    for (slist = certinfo->certinfo[i];
                         slist;
                         slist = slist->next) {
                        // line by line
                        ss << slist->data << "\n";
                    }
                    
                    cert_data.push_back(ss.str());
                }
                
                // add to result
                result.cert_data = cert_data;
                result.success = true;
            }
        }
        delete[] url;
    }
    
    return result;
}

char *convert_hostname_to_url(string domain)
{
    // "https://" and "/"
    constexpr unsigned short SIZE_HTTPS = 8;
    constexpr unsigned short SIZE_SLASH = 1;
    constexpr unsigned short SIZE_OVERHEAD = SIZE_HTTPS + SIZE_SLASH;
    
    char *url = new char[domain.size() + SIZE_OVERHEAD + 1]();
    // + 1 for null termination
    char *copy_pointer = url; // cursor
    
    // protocol
    strncpy(copy_pointer, "https://", SIZE_HTTPS);
    copy_pointer += 8;
    
    // domain
    strncpy(copy_pointer, domain.c_str(), domain.size());
    copy_pointer += domain.size();
    
    // path and C string null termination
    *copy_pointer++ = '/';
    *copy_pointer = '\0';
    
    return url;
}
