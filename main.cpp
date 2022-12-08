#include <iostream>
#include "InputParser.h"
#include "TokenGenerator.h"


void test_truncate();

int main(int argc, char *argv[]) {
//    parser::InputParser input(argc, argv);
//    std::cout << "Hello, World!" << std::endl;

    test_truncate();

//    uint8_t secret [20] = {0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x30};
//    uint8_t count [8] = {0,0,0,0,0,0,0,2};
//
//    std::cout<< cryptlite::hmac<cryptlite::sha1>::calc_hex(count, 8, secret, 20) << std::endl;


return 0;
}

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