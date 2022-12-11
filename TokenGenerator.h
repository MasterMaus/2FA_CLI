//
// Created by maurits on 8-12-22.
//

#ifndef INC_2FA_CLI_TOKENGENERATOR_H
#define INC_2FA_CLI_TOKENGENERATOR_H


#include "include/cryptlite/hmac.h"
#include <boost/algorithm/string.hpp>
#include <regex>
#include <iostream>
#include <ctime>
#include <chrono>
#include <vector>

namespace token_generator {

    // Generates an HOTP token with the key and counter given in the parameters
    std::string gen_OTP(const std::vector<uint8_t> & key, unsigned long counter, int = 6);

    // Generates an TOTP token for the current time
    std::string gen_OTP(const std::vector<uint8_t> & key, int =6);

    // Generates the counter from current time, default value for time_step is 30 seconds. --> for how long is an OTP valid
    unsigned long gen_counter(int = 30);

    // Truncates the hash with the protocol described in RFC4226, and returns the integer
    int truncate(const std::string& hash);

}

#endif //INC_2FA_CLI_TOKENGENERATOR_H
