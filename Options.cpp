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

    void executeOption(const Options option, const std::vector<std::string> args) {
        switch (option) {
            case version:
                executeVersion();
                break;
            case help:
                //executeHelp({})
                break;
        }
    }

    void executeVersion() {
        //TODO get version from CMAKE
        //TODO figure out shit with licenses
        std::cout<<std::endl<<"2fa version 0.1\n"
                              "Copyright blablabla \n"
                              "License blablabla\n"
                              "Written by Maurits Hameter\n"
                              "maurits@hameter.dev\n";
    }

    void executeHelp(const std::string arg) {
        std::cout<<std::endl<<"Usage: 2fa ";
        for (auto&& [option,long_option,short_option,flag,min_arg,max_arg,str] : OPTIONS) {

        }
    }


}