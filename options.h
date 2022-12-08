//
// Created by maurits on 29-11-22.
//

#ifndef CLI_TEST_OPTIONS_H
#define CLI_TEST_OPTIONS_H

#include <tuple>
#include <string>
#include <vector>

const static std::string D_HELP = "Display this help or a command specific help";
const static std::string D_VERSION = "Print current version of this application";

// long-option, short-option, minimum amount of arguments, maximum amount of arguments, description
namespace options {
    std::vector<std::tuple<std::string, char,  int, int, std::string>> OPTIONS {
        std::tuple<std::string, char, int, int, std::string> {"version", 'v', 0, 0, D_VERSION},
        std::tuple<std::string, char, int, int, std::string> {"help", 'h', 0,1,D_HELP}
    };


}


#endif //CLI_TEST_OPTIONS_H
