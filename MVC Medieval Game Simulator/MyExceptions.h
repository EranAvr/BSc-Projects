//
// Created by Eran on 6/9/2023.
//

#ifndef HW3_MYEXCEPTIONS_H
#define HW3_MYEXCEPTIONS_H

#include <exception>
#include <sstream>

namespace MyExceptions{
    struct CustomException : public std::exception {
        std::string message;
    };


    struct ArgsCountException : public CustomException {
        const char* what() const noexcept override{
            return "Error occurred! Program expect exactly two input files.";
        }
    };
    struct IllegalCommandException : public CustomException {
        explicit IllegalCommandException(std::string msg) {message = msg;}
        const char* what() const noexcept override{
            std::string res = "Illegal command given: " + message;
            return res.c_str();
        }
    };

    struct SiteDoesntExistException : public CustomException {
        explicit SiteDoesntExistException(std::string msg) {message = msg;}
        const char* what() const noexcept override{
            std::string res = "Site requested doesn't exist: " + message;
            return res.c_str();
        }
    };
    struct AgentDoesntExistException : public CustomException {
        explicit AgentDoesntExistException(std::string msg) {message = msg;}
        const char* what() const noexcept override{
            std::string res = "Agent requested doesn't exist: " + message;
            return res.c_str();
        }
    };
    struct IllegalAgentNameException : public CustomException {
        const char* what() const noexcept override{
            return "Agent name must be 16 characters maximum.";
        }
    };
    struct IllegalAlphaBetStringException : public CustomException {
        explicit IllegalAlphaBetStringException(std::string msg) {message = msg;}
        const char* what() const noexcept override{
            std::string res = "Illegal character in: " + message + ".\nString must only contain alphabet.";
            return res.c_str();
        }
    };
    struct AttackFailedException : public CustomException {
        explicit AttackFailedException(std::string msg) {message = msg;}
        const char* what() const noexcept override{
            std::string res = "Attack Failed: " + message;
            return res.c_str();
        }
    };
    struct SpeedParameterMissingException : public CustomException {
        const char* what() const noexcept override{
            return "Thug movement command require additional parameter: <speed>";
        }
    };
    struct CharacterIsDeadException : public CustomException {
        const char* what() const noexcept override{
            return "Dead character can't take commands.";
        }
    };
}

#endif //HW3_MYEXCEPTIONS_H
