#include "resp_parser.h"
#include <sstream>
#include <algorithm>

std::vector<std::string> parse_resp2(const std::string &input) {
    std::vector<std::string> args;
    std::istringstream iss(input);
    std::string line;
    size_t num_args = 0;

    while (std::getline(iss, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());

        if (line.empty()) continue;

        if (line[0] == '*') {  
            num_args = std::stoul(line.substr(1));
        } else if (line[0] == '$') {  
            continue;
        } else {  
            args.push_back(line);
        }
        if (num_args != 0 && args.size() >= num_args) break;
    }

    return args;
}
