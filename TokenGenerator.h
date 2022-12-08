//
// Created by maurits on 8-12-22.
//

#ifndef INC_2FA_CLI_TOKENGENERATOR_H
#define INC_2FA_CLI_TOKENGENERATOR_H

#include "include/cryptlite/hmac.h"

namespace token_generator {

    // Generates an HOTP token with the key and counter given in the parameters
    std::string gen_OTP(std::string key, std::string counter);

    // Generates an TOTP token for the current time
    std::string gen_OTP(std::string key);

    // Generates the counter from current time
    std::string gen_counter();

    // Truncates the hash with the protocol described in RFC4226
    std::string truncate(std::string hash);

}

#endif //INC_2FA_CLI_TOKENGENERATOR_H
