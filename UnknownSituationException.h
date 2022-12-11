//
// Created by maurits on 11-12-22.
//

#ifndef INC_2FA_CLI_UNKNOWNSITUATIONEXCEPTION_H
#define INC_2FA_CLI_UNKNOWNSITUATIONEXCEPTION_H

#include <stdexcept>
namespace exceptions {
    class UnknownSituationException
            : public std::exception {

    public:

        // Construct with given error message:
        UnknownSituationException(const char *error = "Functionality not yet implemented!") {
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
#endif //INC_2FA_CLI_UNKNOWNSITUATIONEXCEPTION_H
