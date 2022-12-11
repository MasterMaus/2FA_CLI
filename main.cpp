#include <iostream>
#include <filesystem>
#include <fstream>

#include "InputParser.h"
#include "TokenGenerator.h"

#define PREFIX_NEW_SECRET 0xFFFFFF

#define PREFIX_KEY 0xB0
#define SUFFIX_KEY 0x0D
#define PREFIX_OPTIONS 0xAA

namespace fs = std::filesystem;

void init(fs::path pathToFile); //that checks if the file + path exist

void writeSecret(fs::path path, std::string name, const uint8_t * secret, int secret_len); //function to write a secret into binary file

void test_truncate();
void test_HOTP();

int main(int argc, char *argv[]) {
    fs::path pathToFile = fs::path(getenv("HOME"))
            .append(".config")
            .append("2FA")
            .append("data");
    init(pathToFile);


    parser::InputParser input(argc, argv);


    uint8_t secret [10] = {0x0a,0x6c,0xae,0xcb,0xc2,0xf0,0x70,0xca,0x96,0x73};

    writeSecret(pathToFile, std::string("saxion"), secret, 10);

    //uint8_t secret [10];
    //data.read(reinterpret_cast<char *>(secret), 10);



    std::cout<<token_generator::gen_OTP(secret, 10)<<std::endl;

return 0;
}

void writeSecret(fs::path path, std::string name, const uint8_t * secret, int secret_len) {
    std::ofstream file(path, std::ios::out | std::ios::binary | std::ios::app);

    char prefixSecret [3];
    prefixSecret[0] = PREFIX_NEW_SECRET >> 0;
    prefixSecret[1] = PREFIX_NEW_SECRET >> 8;
    prefixSecret[2] = PREFIX_NEW_SECRET >> 16;

    file.write((prefixSecret), 3);

    uint8_t flag1 = name.size();
    uint8_t flag2 = secret_len;

    file.put(flag1); // options bit + length of the key id in bytes
    file.put(flag2); // length of the secret in bytes

    file.write(name.c_str(), name.size());
    file.write(reinterpret_cast<const char *>(secret), secret_len);

    //todo think about implementing options. like, HOTP, size of the token and time
}



void init(fs::path path) {
    // check if file exists, if not, create one
    if (!fs::exists(path)) {
        if (!fs::exists(path.parent_path())) {
            fs::create_directories(path.parent_path());
        }
        //data file does not exist, create one
        std::ofstream file(path, std::ios::out| std::ios::binary);
        file.close();
    }
}

// tester functions
void test_truncate() {
    // https://www.rfc-editor.org/rfc/rfc4226#page-32
    assert(token_generator::truncate("cc93cf18508d94934c64b65d8ba7667fb7cde4b0") == 1284755224);
    assert(token_generator::truncate("75a48a19d4cbe100644e8ac1397eea747a2d33ab") == 1094287082);
    assert(token_generator::truncate("0bacb7fa082fef30782211938bc1c5e70416ff44") == 137359152);
    assert(token_generator::truncate("66c28227d03a2d5529262ff016a1e6ef76557ece") == 1726969429);
    assert(token_generator::truncate("a904c900a64b35909874b33e61c5938a8e15ed1c") == 1640338314);
    assert(token_generator::truncate("a37e783d7b7233c083d4f62926c7a25f238d0316") == 868254676);
    assert(token_generator::truncate("bc9cd28561042c83f219324d3c607256c03272ae") == 1918287922);
    assert(token_generator::truncate("a4fb960c0bc06e1eabb804e5b397cdc4b45596fa") == 82162583);
    assert(token_generator::truncate("1b3c89f65e6c9e883012052823443f048b4332db") == 673399871);
    assert(token_generator::truncate("1637409809a679dc698207310c8c7fc07290d9e5") == 645520489);
}

void test_HOTP() {
    // 12345678901234567890 (ASCII) becomes secret[20]
    uint8_t secret [20] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30};

    //https://www.ietf.org/rfc/rfc6238.txt page 14
    assert(token_generator::gen_OTP(secret, 20, 0x1,8).compare(std::string("94287082"))==0);
    assert(token_generator::gen_OTP(secret, 20, 0x23523EC,8).compare(std::string("07081804"))==0);
    assert(token_generator::gen_OTP(secret, 20, 0x23523ED,8).compare(std::string("14050471"))==0);
    assert(token_generator::gen_OTP(secret, 20, 0x273EF07,8).compare(std::string("89005924"))==0);
    assert(token_generator::gen_OTP(secret, 20, 0x3F940AA,8).compare(std::string("69279037"))==0);
    assert(token_generator::gen_OTP(secret, 20, 0x27BC86AA,8).compare(std::string("65353130"))==0);
}