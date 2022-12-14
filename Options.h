//
// Created by maurits on 29-11-22.
//

#ifndef CLI_TEST_OPTIONS_H
#define CLI_TEST_OPTIONS_H

#include <tuple>
#include <string>
#include <vector>
#include <map>

#include "InvalidArgumentsException.h"
#include "NotImplementedException.h"
#include <iostream>
#include "Key.h"

#include <filesystem>

namespace fs = std::filesystem;

#define LONG_OPTION 0
#define SHORT_OPTION 1
#define FLAG 2
#define MIN_ARG 3
#define MAX_ARG 4
#define DESCRIPTION 5

// TODO potentially, set this to default, let it be able to change from a .config file in home folder
const static fs::path PATH_TO_FILE = fs::path(getenv("HOME"))
        .append(".config")
        .append("2FA")
        .append("data");

// long-option, short-option, flag, minimum amount of arguments, maximum amount of arguments, description
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
                                          "The program defaults to this option when no options are set."; //add specific posix_options for how many tokens, add the window of validity next to it


    const static std::map<Options, std::tuple<std::string, char, bool, int, int, std::string> > OPTIONS {
            {version, {"version", 'v', true, 0, 0, D_VERSION}},
            {help, {"help", 'h', false, 0, 1, D_HELP}},
            {add, {"add", 'a', false, 2, 2, D_ADD}}, // actually might need max 3 args; id, secret, encoding
//        {remove, {"remove", 'r', false, 1, 1, D_REMOVE}},
            {generate, {"generate", 'g', false, 1, 2, D_GENERATE}}
    };


    //helper functions to translate option identifier to enum
    Options find(char c);
    Options find(std::string s);

    bool isFlag(Options o);

    //big switch statement
    void executeOption(const Options option, const std::vector<std::string>);

    void executeVersion();
    void executeHelp(const std::string arg = "");
    void executeAdd(const std::string id, const std::string key, const mfa::encoding = mfa::encoding::B32);
    void executeRemove();
    void executeGenerate(const std::string id); //DEFAULT
}


#endif //CLI_TEST_OPTIONS_H
