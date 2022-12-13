//
// Created by maurits on 11-12-22.
//

#ifndef INC_2FA_CLI_INVALIDARGUMENTSEXCEPTION_H
#define INC_2FA_CLI_INVALIDARGUMENTSEXCEPTION_H

#include <stdexcept>
namespace exceptions {
    class InvalidArgumentsException
            : public std::exception {

    public:

        // Construct with given error message:
        InvalidArgumentsException(const char *error = "One of the arguments added to the program is invalid") {
            errorMessage = error;
        }

        // Provided for compatibility with std::exception.
        const char *what() const noexcept {
            return errorMessage.c_str();
        }

    private:

        std::string errorMessage;
    };
}
#endif //INC_2FA_CLI_INVALIDARGUMENTSEXCEPTION_H
