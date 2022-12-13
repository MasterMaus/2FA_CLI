//
// Created by maurits on 29-11-22.
//

#ifndef CLI_TEST_OPTIONS_H
#define CLI_TEST_OPTIONS_H

#include <tuple>
#include <string>
#include <vector>



// long-option, short-option, minimum amount of arguments, maximum amount of arguments, description
namespace posix_options {

    enum Options {
        version, help, add, remove, generate,invalid
    };


    const static std::string D_HELP = "Display this help or a command specific help";
    const static std::string D_VERSION = "Print current version of this application. May be called with any other option";
    const static std::string D_ADD = "Add a key to the database. The key is by default decoded in base32"; // add specific posix_options for keysize, length of validity, different encoding.
    const static std::string D_REMOVE = "Remove a key from the database.";
    const static std::string D_GENERATE = "Generate the current valid token. This option needs to get a valid identifier.\n"
                                          "A number n may be added after the identifier to generate the current + n tokens after. \n"
                                          "The program defaults to this option when only an identifier is passed"; //add specific posix_options for how many tokens, add the window of validity next to it



    const static std::vector<
            std::tuple<Options, std::string, char, bool, int, int, std::string>> OPTIONS {
        std::tuple<Options, std::string, char, bool, int, int, std::string> {version, "version", 'v', true, 0, 0, D_VERSION},
        std::tuple<Options, std::string, char, bool, int, int, std::string> {help, "help", 'h', true, 0, 1, D_HELP},
        std::tuple<Options, std::string, char, bool, int, int, std::string> {add, "add", 'a', false, 2, 2, D_ADD},
//        std::tuple<posix_options, std::string, char, bool, int, int, std::string> {remove, "remove", 'r', false, 1, 1, D_REMOVE},
        std::tuple<Options, std::string, char, bool, int, int, std::string> {generate, "generate", 'g', false, 1, 2, D_GENERATE}
    };

    //helper to translate option identifier to enum
    Options find(char c);
    Options find(std::string s);

    //big switch statement
    void executeOption(const Options option, const std::vector<std::string>);

    void executeVersion();
    void executeHelp(const std::string arg = "");
//    static void executeAdd(); // what arguments are passed, and how are those differentiated ;P
    void executeRemove();
    void executeGenerate(); //DEFAULT
}


#endif //CLI_TEST_OPTIONS_H
