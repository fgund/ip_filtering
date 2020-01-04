#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "ip4.h"
#include "filter.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main()
{
    try
    {
        std::vector<ip4> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.empty()) break;
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back({v[0]});
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),std::greater<ip4>());
        for(auto &cur_ip : ip_pool)
        {
            std::cout << cur_ip <<std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        std::cout << "Filter 1:" <<std::endl;
        auto ip_1 = filter(ip_pool,[](ip4 ip){ return (ip>=ip4{1,0,0,0} && ip<ip4{2,0,0,0});});
        for(auto &cur_ip : ip_1)
        {
            std::cout << cur_ip <<std::endl;
        }
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        std::cout << "Filter 46, 70:" <<std::endl;
        auto ip_46_70 = filter(ip_pool,[](ip4 ip){ return (ip>=ip4{46,70,0,0} && ip<ip4{46,71,0,0});});
        for(auto &cur_ip : ip_46_70)
        {
            std::cout << cur_ip <<std::endl;
        }
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        std::cout << "Filter 46 any:" <<std::endl;
        auto ip_any_46 = filter(ip_pool,[](ip4 ip) {
            unsigned char value = 46;
            bool hasValue = false;
            std::vector<std::string> ip_bytes = split(ip.to_string(), '.');
            for(std::string &b : ip_bytes)
            {
                if(stoi(b) == value)
                {
                    hasValue = true;
                    break;
                }
            }

            return hasValue;
        });
        for(auto &cur_ip : ip_any_46)
        {
            std::cout << cur_ip <<std::endl;
        }
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
