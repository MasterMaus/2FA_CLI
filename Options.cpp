//
// Created by maurits on 13-12-22.
//

#include <iostream>
#include "Options.h"

namespace posix_options {

    Options find(char c) {
        for (auto option: OPTIONS) {
            if (std::get<2>(option) == c) return std::get<0>(option);
        }
        return invalid;
    }

    Options find(std::string s) {
        for (auto option: OPTIONS) {
            if (std::get<1>(option) == s) return std::get<0>(option);
        }
        return invalid;
    }

    bool isFlag(Options o) {
        for (auto option: OPTIONS) {
            if (std::get<0>(option) == o) return std::get<3>(option);
        }
        throw exceptions::InvalidArgumentsException();
    }


    void executeOption(const Options option, const std::vector<std::string> args) {
        switch (option) {
            case version:
                executeVersion();
                break;
            case help:
                if (args.empty()) {
                    executeHelp();
                } else {
                    executeHelp(args[0]);
                }
                break;
        }
    }

    void executeVersion() {
        //TODO get version from CMAKE
        //TODO figure out shit with licenses
        std::cout << std::endl << "2fa version 0.1\n"
                                  "Copyright blablabla \n"
                                  "License blablabla\n"
                                  "Written by Maurits Hameter\n"
                                  "maurits@hameter.dev\n";
    }

    void executeHelp(const std::string arg) {
        std::cout << std::endl << "Usage: 2fa [OPTION]...\n"
                                  "Generates a 2FA token for a specified key\n"
                                  "\n"
                                  "Mandatory arguments to long options are mandatory for short options too.\n";

        if (arg == "") {
            //standard help
            for (auto &&[option, long_option, short_option, flag, min_arg, max_arg, str_help]: OPTIONS) {
                std::cout << '-' << short_option << "\t --" << long_option << "\t\t" << str_help << std::endl;
            }
        } else {
            //specific help
        }
    }


}