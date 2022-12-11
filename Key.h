//
// Created by maurits on 11-12-22.
//

#ifndef INC_2FA_CLI_KEY_H
#define INC_2FA_CLI_KEY_H

#include <utility>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#include "NotImplementedException.h"
#include "UnknownSituationException.h"

namespace fs = std::filesystem;

namespace b32 {
    const char dectable[128] = {
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, 26, 27, 28, 29, 30, 31, -1, -1, -1, -1, -1, 0, -1, -1,
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
            -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1
    };

    static std::vector<uint8_t> base32decode(std::string msg) {
        std::vector<uint8_t> res{};

        int pad = 0;
        while (msg.size() % 8 != 0) {
            msg += '='; //message is not a block of 8 letters, needs padding
            pad++;
        }
        for (int i = 0; i < msg.size(); i += 8) {
            unsigned long decoded = 0;
            auto block = msg.substr(i, 8);

            int byte = 5;

            for (auto c: block) {
                if (c == '=') {
                    switch (pad) {
                        case 6:
                            // 1 byte of data
                            byte = 1;
                            decoded >>= 2;
                            break;
                        case 4:
                            // 2 bytes of data
                            byte = 2;
                            decoded >>= 4;
                            break;
                        case 3:
                            // 3 bytes of data
                            byte = 3;
                            decoded >>= 1;
                            break;
                        case 1:
                            // 4 bytes of data
                            byte = 4;
                            decoded >>= 3;
                            break;
                        case 0:
                            //take all 5 bytes is data
                            byte = 5;
                            break; // do nothing
                        default:
                            throw exceptions::UnknownSituationException(
                                    "the amount of padding characters is illegal");
                    }
                    break;
                }
                decoded = decoded << 5;
                decoded += b32::dectable[toascii(c)];
            }

            for (; byte > 0; byte--) {
                res.push_back((uint8_t) (decoded >> (byte - 1) * 8));
            }
        }

        return res;
    }
}

namespace mfa {
    enum encoding {
        B32, B64
    };

    class Key {
    public:
        // constructors
        Key(std::string id, const uint8_t *secret, int secret_len) : m_id{std::move(id)}, m_key{secret, secret + secret_len} {

        }

        Key(std::string id, std::string secret, encoding enc = encoding::B32) : m_id{std::move(id)} {
            switch (enc) {
                case encoding::B32 :
                    m_key = b32::base32decode(secret);
                    break;
                case encoding::B64 :
                    throw exceptions::NotImplementedException();
                    break;
                default :
                    throw std::exception();

            }
        }

        Key(std::string id, const fs::path& path) : m_id{std::move(id)} {
            throw exceptions::NotImplementedException("This constructor relies on loadFromFile() function, which is not finished yet");

        }



    private:
        std::string m_id;
        std::vector<uint8_t> m_key;
        bool m_totp = true; // in case of HOTP, set to false
        int m_ttl = 30; // Only relevant if TOTP is used
        long long m_counter = 0; // Only relevant if HOTP is used
    };
}

#endif //INC_2FA_CLI_KEY_H
