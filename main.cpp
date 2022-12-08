#include <iostream>
#include "InputParser.h"
#include "TokenGenerator.h"

int main(int argc, char *argv[]) {
    parser::InputParser input(argc, argv);
    std::cout << "Hello, World!" << std::endl;

    token_generator::truncate(std::string("32c936988a511d9a2f2565069394a0117030f666"));
    return 0;
}
