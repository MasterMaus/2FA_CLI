//
// Created by maurits on 29-11-22.
//

#ifndef CLI_TEST_OPTIONS_H
#define CLI_TEST_OPTIONS_H

#include <tuple>
#include <string>
#include <vector>



// long-option, short-option, minimum amount of arguments, maximum amount of arguments, description
namespace options {

    enum options {
        version, help, add, remove, generate,invalid
    };


    const static std::string D_HELP = "Display this help or a command specific help";
    const static std::string D_VERSION = "Print current version of this application. May be called with any other option";
    const static std::string D_ADD = "Add a key to the database. The key is by default decoded in base32"; // add specific options for keysize, length of validity, different encoding.
    const static std::string D_REMOVE = "Remove a key from the database.";
    const static std::string D_GENERATE = "Generate the current valid token. This option needs to get a valid identifier.\n"
                                          "A number n may be added after the identifier to generate the current + n tokens after. \n"
                                          "The program defaults to this option when only an identifier is passed"; //add specific options for how many tokens, add the window of validity next to it



    const static std::vector<
            std::tuple<options, std::string, char, bool, int, int, std::string>> OPTIONS {
        std::tuple<options, std::string, char, bool, int, int, std::string> {version, "version", 'v', true, 0, 0, D_VERSION},
        std::tuple<options, std::string, char, bool, int, int, std::string> {help, "help", 'h', false, 0,1,D_HELP},
        std::tuple<options, std::string, char, bool, int, int, std::string> {add, "add", 'a', false, 2,2, D_ADD},
//        std::tuple<options, std::string, char, bool, int, int, std::string> {remove, "remove", 'r', false, 1, 1, D_REMOVE},
        std::tuple<options, std::string, char, bool, int, int, std::string> {generate, "generate", 'g', false, 1, 2, D_GENERATE}
    };

    static options find(char c) {
        for (auto option : OPTIONS) {
            if (std::get<2>(option) == c) return std::get<0>(option);
        }
        return invalid;
    }

    static options find(std::string s) {
        for (auto option : OPTIONS) {
            if (std::get<1>(option) == s) return std::get<0>(option);
        }
        return invalid;
    }


}


#endif //CLI_TEST_OPTIONS_H
