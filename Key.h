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

#define PREFIX_NEW_SECRET 0xFFFFFF
#define PREFIX_OPTIONS 0xAA



namespace fs = std::filesystem;

namespace b32 {
    const static char DECTABLE[128] = {
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
                if(b32::DECTABLE[toascii(c)] == -1) {
                    throw exceptions::UnknownSituationException("this string contains a non valid base32 character");
                }
                decoded += b32::DECTABLE[toascii(c)];
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
        Key(std::string id, std::string secret, encoding enc = encoding::B32) : m_id{std::move(id)} {
            switch (enc) {
                case encoding::B32 :
                    m_key = b32::base32decode(std::move(secret));
                    break;
                case encoding::B64 :
                    throw exceptions::NotImplementedException();
                    break;
                default :
                    throw std::exception();

            }
        }

        Key(std::string id, const fs::path& path) : m_id{std::move(id)} {

            std::ifstream file{path, std::ios::in | std::ios::binary};
            bool match = false;

            uint8_t key_len;

            while (!match) {
                nextSecret(file); // set read pointer to the start of the next secret
                if(file.eof()) break;
                uint8_t flag1 = file.get();
                key_len = file.get();

                if (flag1 >> 7 == 0x01) {
                    // option flag has been set
                    flag1 &= 0x7f;
                    throw exceptions::NotImplementedException();
                }
                std::string name {};
                for (int i = 0; i < flag1; i++) {
                    name += (char) file.get();
                }
                if (m_id == name) match = true;
            }

            if (match) {
                for (int i = 0; i < key_len; i++) {
                    m_key.push_back(file.get());
                }
            } else {
                throw exceptions::NotImplementedException();
                //TODO throw different custom exception that i catch somewhere else
            }

        }

        void writeSecret(const fs::path& path) {
            std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::app);

            char prefixSecret [3];
            prefixSecret[0] = (char) (PREFIX_NEW_SECRET >> 0);
            prefixSecret[1] = (char) (PREFIX_NEW_SECRET >> 8);
            prefixSecret[2] = (char) (PREFIX_NEW_SECRET >> 16);

            file.write((prefixSecret), 3);

            uint8_t flag1 = m_id.size();
            uint8_t flag2 = m_key.size();

            file.put((char) flag1); // options bit + length of the key id in bytes
            file.put((char) flag2); // length of the secret in bytes

            file.write(m_id.c_str(),m_id.size());
            for(auto c : m_key) {
                file.put((char)c);
            }
            //todo think about implementing options. like, HOTP, size of the token and time
        }

        static void nextSecret(std::ifstream &stream) {
            int count = 0;
            while (count != 3 && !stream.eof()) {
                if (stream.get() == 0xff) count++;
            }
        }

        std::string getOTP() {
            if (m_totp) {
                // TOTP
                return token_generator::gen_OTP(m_key);
            } else {
                throw exceptions::NotImplementedException();
            }
        }


    private:
        std::string m_id;
        std::vector<uint8_t> m_key;
        bool m_totp = true; // in case of HOTP, set to false
        int m_ttl = 30; // Only relevant if TOTP is used, by default this is 30
        int m_otp_len = 6; // number of digits, by default this is 6
        long long m_counter = 0; // Only relevant if HOTP is used
    };
}

#endif //INC_2FA_CLI_KEY_H
