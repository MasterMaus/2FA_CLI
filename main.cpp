#include <iostream>
#include <filesystem>
#include <fstream>

#include "InputParser.h"
#include "TokenGenerator.h"
#include "Key.h"

#include "UnknownSituationException.h"

namespace fs = std::filesystem;

// main functions
void init(const fs::path& pathToFile); //that checks if the file + path exist


//test functions
void test_truncate();
void test_HOTP();





int main(int argc, char *argv[]) {
    fs::path pathToFile = fs::path(getenv("HOME"))
            .append(".config")
            .append("2FA")
            .append("data");
    init(pathToFile);


    parser::InputParser input(argc, argv);

    std::cout << input.count();

return 0;
}





void init(const fs::path& path) {
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
    std::vector<uint8_t> secret = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30};

    //https://www.ietf.org/rfc/rfc6238.txt page 14
    assert(token_generator::gen_OTP(secret, 0x1,8) == std::string("94287082"));
    assert(token_generator::gen_OTP(secret, 0x23523EC,8) == std::string("07081804"));
    assert(token_generator::gen_OTP(secret, 0x23523ED,8) == std::string("14050471"));
    assert(token_generator::gen_OTP(secret, 0x273EF07,8) == std::string("89005924"));
    assert(token_generator::gen_OTP(secret, 0x3F940AA,8) == std::string("69279037"));
    assert(token_generator::gen_OTP(secret, 0x27BC86AA,8) == std::string("65353130"));
}