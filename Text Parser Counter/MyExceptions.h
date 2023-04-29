//
// Created by Eran on 6/27/2021.
//

#ifndef HW5_MYEXCEPTIONS_H
#define HW5_MYEXCEPTIONS_H

#include <exception>
using namespace std;

namespace MyExceptions{
    class xEmptyCounter : public exception{
        const char * what () const throw () {
            return "Error: Counter is empty";
        }
    };
    class xFileFailure : public exception{
        const char * what () const throw () {
            return "Error: Failed to open file";
        }
    };
    class xReadFailure : public exception{
        const char * what () const throw () {
            return "Error: Read failed";
        }
    };
    class xCounterAlreadyExists : public exception{
        const char * what () const throw () {
            return "Error: Counter name already exists";
        }
    };
    class xMissingCounterName : public exception{
        const char * what () const throw () {
            return "Error: Missing counter name";
        }
    };
    class xMissingFileName : public exception{
        const char * what () const throw () {
            return "Error: Missing file name";
        }
    };
    class xMissingFile : public exception{
    public:
        xMissingFile(const string& _msg)  : msg(_msg){}
        virtual ~xMissingFile() throw(){}
        const char * what () const throw () {
            string error = "Error: Missing file " + msg;
            return error.c_str();
        }
    private:
        string msg;
    };
    class xUnknownCommand : public exception{
    public:
        xUnknownCommand(const string& _msg)  : msg(_msg){}
        virtual ~xUnknownCommand() throw(){}
        const char * what () const throw () {
            string error = "Error: Unknown command " + msg;
            return error.c_str();
        }
    private:
        string msg;
    };
    class xCounterDoeasntExists : public exception{
    public:
        xCounterDoeasntExists(const string& _msg)  : msg(_msg){}
        virtual ~xCounterDoeasntExists() throw(){}
        const char * what () const throw () {
            string error = "Error: No counter named " + msg;
            return error.c_str();
        }
    private:
        string msg;
    };
}

#endif //HW5_MYEXCEPTIONS_H
