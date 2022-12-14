//
// Created by maurits on 8-12-22.
//
#ifndef CLI_TEST_INPUTPARSER_H
#define CLI_TEST_INPUTPARSER_H

#include <vector>
#include <iostream>
#include <map>
#include "Options.h"

#include "InvalidArgumentsException.h"

// https://trailheadtechnology.com/one-dash-vs-two-dashes-in-shell-commands/
// https://medium.com/geekculture/how-to-build-a-cli-app-from-scratch-in-c-f245510e63ac (specifically, how do you add it to /usr/bin/
// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c (input parser)
//

// Below POSIX style command line posix_options (https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html)
// * Arguments are posix_options if they begin with a hyphen delimiter (‘-’).
// * Multiple posix_options may follow a hyphen delimiter in a single token if the posix_options do not take arguments. Thus, ‘-abc’ is equivalent to ‘-a -b -c’.
// * Option names are single alphanumeric characters (as for isalnum; see Classification of Characters).
// * Certain posix_options require an argument. For example, the -o option of the ld command requires an argument—an output file name.
// * An option and its argument may or may not appear as separate tokens. (In other words, the whitespace separating them is optional.) Thus, -o foo and -ofoo are equivalent. (I skip this req)
// * Options typically precede other non-option arguments. (posix_options ALWAYS precede other non-option arguments.)


namespace parser {
    class InputParser {
    public:
        // constructor for input class
        InputParser(int &argc, char *argv[]) {
            for (int i = 1; i < argc; i++) { // argument 0 is the application
                std::string arg{(std::string(argv[i]))};
                if (arg.starts_with("--")) {
                    // long option found
                    posix_options::Options option = posix_options::find(arg.substr(2)); // take only the part after --

                    std::vector<std::string> args = {};
                    int min_args = std::get<MIN_ARG>(posix_options::OPTIONS.at(option));
                    int max_args = std::get<MAX_ARG>(posix_options::OPTIONS.at(option));

                    for (int a = 0; a < max_args; a++) {
                        if (i+1 >= argc) {
                            break; // no more arguments
                        }
                        auto argument = std::string(argv[i+1]); // this cant break, because we test if there is at least one more string
                        if (argument.starts_with('-')) {
                            // this is not an argument!!
                            break;
                        }
                        args.push_back(argument);
                        i++;
                    }
                    if (args.size() < min_args || args.size() > max_args) {
                        throw exceptions::InvalidArgumentsException("not enough or too many arguments for this option!");
                    }

                    m_options[option] = args;

                } else if (arg.starts_with("-")) {
                    if (arg.size() !=2) {
                        //flags
                        for (auto c : arg) {
                            if(c == '-') continue;

                            posix_options::Options flag = posix_options::find(c);
                            if (flag == posix_options::Options::invalid || !posix_options::isFlag(flag))
                                throw exceptions::InvalidArgumentsException();

                            m_options[flag] = {};
                        }
                    } else {
                        //short option (not a flag!!!)
                        posix_options::Options option = posix_options::find(arg[1]);

                        std::vector<std::string> args = {};
                        int min_args = std::get<MIN_ARG>(posix_options::OPTIONS.at(option));
                        int max_args = std::get<MAX_ARG>(posix_options::OPTIONS.at(option));

                        for (int a = 0; a < max_args; a++) {
                            if (i+1 >= argc) {
                                break; // no more arguments
                            }
                            auto argument = std::string(argv[i+1]); // this cant break, because we test if there is at least one more string
                            if (argument.starts_with('-')) {
                                // this is not an argument!!
                                break;
                            }
                            args.push_back(argument);
                            i++;
                        }
                        if (args.size() < min_args || args.size() > max_args) {
                            throw exceptions::InvalidArgumentsException("not enough or too many arguments for this option!");
                        }

                        m_options[option] = args;
                    }
                } else {
                    // default option (generate)
                    posix_options::Options option = posix_options::Options::generate;

                    std::vector<std::string> args = {};
                    int min_args = std::get<MIN_ARG>(posix_options::OPTIONS.at(option));
                    int max_args = std::get<MAX_ARG>(posix_options::OPTIONS.at(option));

                    for (int a = 0; a < max_args; a++) {
                        if (i >= argc) {
                            break; // no more arguments
                        }
                        auto argument = std::string(argv[i]); // The thing on i is already an argument, not an option
                        if (argument.starts_with('-')) {
                            // this is not an argument!!
                            break;
                        }
                        args.push_back(argument);
                        i++;
                    }
                    if (args.size() < min_args || args.size() > max_args) {
                        throw exceptions::InvalidArgumentsException("not enough or too many arguments for this option!");
                    }

                    m_options[option] = args;

                    if (i < argc) {
                        // there are still options or arguments, but this is illegal!
                        throw exceptions::InvalidArgumentsException("Too many arguments!");
                    }
                }
            }
        }

        int count() {
            return m_options.size();
        }

        const std::map<posix_options::Options, std::vector<std::string> > getmap() {
            return m_options;
        }

    private:
        std::map<posix_options::Options, std::vector<std::string> > m_options; //use map
    };

#endif //CLI_TEST_INPUTPARSER_H
}