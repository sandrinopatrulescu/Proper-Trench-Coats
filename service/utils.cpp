//
// Created by kamui on 12.04.2021.
//

#include "utils.h"

std::vector<std::string> tokenize(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::stringstream ss(str);
    std::string token;
    while(getline(ss, token, delimiter)){
        result.push_back(token);
    }
    return result;
}
