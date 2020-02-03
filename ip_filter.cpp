#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "ip4.h"
#include "filter.h"

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
        // processing input
        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.empty()) break;
            std::vector<std::string> v = split(line, '\t');
            ip_pool.emplace_back(v[0]);
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(),ip_pool.end(),std::greater<ip4>());
        for(auto &cur_ip : ip_pool)
        {
            std::cout << cur_ip <<std::endl;
        }

        // filter by first byte and output
        // ip = filter(1)
        auto ip_1 = filter(ip_pool,[](ip4 ip){ return (ip>=ip4{1,0,0,0} && ip<ip4{2,0,0,0});});
        for(auto &cur_ip : ip_1)
        {
            std::cout << cur_ip <<std::endl;
        }


        // filter by first and second bytes and output
        // ip = filter(46, 70)
        auto ip_46_70 = filter(ip_pool,[](ip4 ip){ return (ip>=ip4{46,70,0,0} && ip<ip4{46,71,0,0});});
        for(auto &cur_ip : ip_46_70)
        {
            std::cout << cur_ip <<std::endl;
        }

        // filter by any byte and output
        // ip = filter_any(46)
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
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
