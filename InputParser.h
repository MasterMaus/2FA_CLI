//
// Created by maurits on 8-12-22.
//
#ifndef CLI_TEST_INPUTPARSER_H
#define CLI_TEST_INPUTPARSER_H

#include <vector>
#include <iostream>
#include "options.h"

// https://trailheadtechnology.com/one-dash-vs-two-dashes-in-shell-commands/
// https://medium.com/geekculture/how-to-build-a-cli-app-from-scratch-in-c-f245510e63ac (specifically, how do you add it to /usr/bin/
// https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c (input parser)
//

// Below POSIX style command line options (https://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html)
// * Arguments are options if they begin with a hyphen delimiter (‘-’).
// * Multiple options may follow a hyphen delimiter in a single token if the options do not take arguments. Thus, ‘-abc’ is equivalent to ‘-a -b -c’.
// * Option names are single alphanumeric characters (as for isalnum; see Classification of Characters).
// * Certain options require an argument. For example, the -o option of the ld command requires an argument—an output file name.
// * An option and its argument may or may not appear as separate tokens. (In other words, the whitespace separating them is optional.) Thus, -o foo and -ofoo are equivalent. (I skip this req)
// * Options typically precede other non-option arguments. (options ALWAYS precede other non-option arguments.)


namespace parser {
    class InputParser {
    public:
        // constructor for input class
        InputParser(int &argc, char *argv[]) {

            for (auto x: options::OPTIONS) {
                std::cout << std::get<0>(x) << ", " << std::get<1>(x) << ", " << std::get<2>(x) << std::endl;
            }
            // test lines
            std::cout << "There are " << argc << " arguments" << std::endl;
            for (int i = 1; i < argc; i++) { // argument 0 is the application
                std::string arg{(std::string(argv[i]))};
                if (arg.starts_with('-')) {
                    // found 1 or more options
                } else if (arg.starts_with("--")) {
                    // long option found
                }
                std::cout << arg << std::endl;
                //this -> m_tokens.push_back(std::string(argv[i]));

                //std::cout << argv[i] << std::endl;
            }
        }

    private:
        std::vector <std::pair<std::string, std::vector < std::string>>>
        m_tokens; // key-value where the key is the option and the value is its arguments if any
        //TODO
        // Q: where do i specify if an option has 0, 1, defined or undefined ammount of arguments
        // A: Could be solved by reading a file of some sorts. However, I think the valid options + amount of arguments should be known at compile time
        // A2: solve by declaring all of this in a header file
        //
        //TODO
        // if an option has undefined amount of arguments, how does the program know something is a non-option argument or option argument.
        // However, both the ls as the TOTP don't have this problem
    };

#endif //CLI_TEST_INPUTPARSER_H
}