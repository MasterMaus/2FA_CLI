//
// Created by maurits on 8-12-22.
//
#include "TokenGenerator.h"
#include "include/cryptlite/sha1.h"



namespace token_generator {

// Generates an HOTP token with the key and counter given in the parameters
    std::string gen_OTP(std::string key, unsigned long counter, int n) {
        assert(6 >= n <= 10); // According to RFC4226 standards. 6 is default. up to 10 numbers is possible

        uint8_t message[8];

        for (int i = 8; i >= 0; i--)
        {
            message[i] = counter & 0xff;
            counter >>= 8;
        }

        boost::to_upper(key); // Make the key uppercase
        std::string hash = cryptlite::hmac<cryptlite::sha1>::calc_hex(message, 8, (uint8_t *) key.c_str(), key.size());
        std::cout<< hash << std::endl;
        auto otp = truncate(hash) % (int) pow(10,n);

        // TODO: do i really need a stringstream to do this?
        std::stringstream ss;
        ss << std::setw(n) << std::setfill('0') << otp;
        return ss.str();
    }

// Generates an TOTP token for the current time
    std::string gen_OTP(std::string key, int n) {
        auto counter = gen_counter();
        return gen_OTP(key, counter, n);
    }

// Generates the counter from current time
    unsigned long gen_counter() {
        return 1;
    }

    int truncate(std::string hash) {
        assert(std::regex_match(hash,std::regex("[0-9a-f]{40}"))); //Make sure that the hash is a 20 byte hexadecimal string

        auto offset = std::stoi(hash.substr(39,1), 0, 16) * 2; // offset in bytes. multiply by 2 to get the offset in string characters

        auto otp = std::stol(hash.substr(offset,8),0,16); // call string to long, since string to int will crash if the sign bit is checked

        otp &= 0x7FFFFFFF; // flip the sign bit

        return (int)otp;
    }


}