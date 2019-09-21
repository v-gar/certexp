#include "main.hpp"

using std::cout;
using std::cerr;
using std::endl;

/**
 * Main application
 */
int application(std::string config_file)
{
    // Config
    Config config = Config(config_file);
    if (!config.parse()) {
        cerr << "Parsing unsuccessful" << endl;
        return EXIT_FAILURE;
    }
    
    // Retrieve certs
    std::unordered_map<std::string, CertificateChain> cert_info{};
    for (std::string domain_name : config.get_domains()) {
        cout << "Domain: " << domain_name << '\n';
        struct fetch_result res = fetch(domain_name);
        
        CertificateChain c = CertificateChain(res);
        
        for (auto element : c.get_certs()) {
            cout << "Expire date: "
                 << std::asctime(&element.second)
                 << " (expires in " 
                 << get_expire_day_difference(&element.second) << " days)\n"
                 << " (SAN: " << element.first << ")\n";
        }
        
        cout << endl;
    }
    
    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    if (argc > 1)
        return application(argv[1]);
    else {
        cout << "Error: no config file specified." << endl;
        return EXIT_FAILURE;
    }
}
