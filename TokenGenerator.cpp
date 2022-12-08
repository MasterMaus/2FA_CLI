//
// Created by maurits on 8-12-22.
//
#include "TokenGenerator.h"
#include "include/cryptlite/sha1.h"



namespace token_generator {

// Generates an HOTP token with the key and counter given in the parameters
    std::string gen_OTP(std::string key, std::string counter) {
        std::string hash = cryptlite::hmac<cryptlite::sha1>::calc_hex(counter, key);



        return std::string();
    }

// Generates an TOTP token for the current time
    std::string gen_OTP(std::string key) {
        auto counter = gen_counter();
        return gen_OTP(key, counter);
    }

// Generates the counter from current time
    std::string gen_counter() {
        return std::string();
    }

    std::string truncate(std::string hash) {
        assert(hash.length() == 40);
        return std::string();
    }


}