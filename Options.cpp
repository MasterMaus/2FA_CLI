//
// Created by maurits on 13-12-22.
//

#include "Options.h"



namespace posix_options {

    Options find(char c) {
        for (auto&& [option, properties] : OPTIONS) {
            if (std::get<SHORT_OPTION>(properties) == c) return option;
        }
        return invalid;
    }

    Options find(std::string s) {
        for (auto&& [option, properties] : OPTIONS) {
            if (std::get<LONG_OPTION>(properties) == s) return option;
        }
        return invalid;
    }

    bool isFlag(Options o) {
        for (auto&& [option, properties] : OPTIONS) {
            if (option == o) return std::get<FLAG>(properties);
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
            case add:
                executeAdd(args.at(0), args.at(1));
                break;
            case remove:
                executeRemove();
                break;
            case generate:
                //TODO do different things if there are more arguments!
                executeGenerate(args.at(0));
            default:
                throw exceptions::InvalidArgumentsException("Trying to execute a non existant option");
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
            for (auto &&[option, properties] : OPTIONS) {
                auto short_option = std::get<SHORT_OPTION>(properties);
                auto long_option = std::get<LONG_OPTION>(properties);
                auto str_help = std::get<DESCRIPTION>(properties);
                std::cout << '-' << short_option << "\t --" << long_option << "\t\t" << str_help << std::endl;
            }
        } else {
            //specific help
            auto properties = OPTIONS.at(find(arg));
            auto short_option = std::get<SHORT_OPTION>(properties);
            auto long_option = std::get<LONG_OPTION>(properties);
            auto str_help = std::get<DESCRIPTION>(properties);
            std::cout << '-' << short_option << "\t --" << long_option << "\t\t" << str_help << std::endl;
        }
    }

    void executeAdd(const std::string id, const std::string key, const mfa::encoding) {
        throw exceptions::NotImplementedException("executeAdd");
    }

    void executeRemove() {
        throw exceptions::NotImplementedException("executeRemove");
    }

    void executeGenerate(const std::string id) {
        auto generator = mfa::Key(id, PATH_TO_FILE);
        std::cout<<generator.getOTP()<<std::endl;
    }


}