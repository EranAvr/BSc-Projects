//
// Created by Eran on 6/26/2021.
//

#include "Parser.h"

void Parser::start() {
    string line;

    while (getline(cin, line)){
        string command, counter_name, file_name;
        stringstream ss(line);
        if (ss.fail()){
            throw MyExceptions::xReadFailure();
        }
        ss >> command;
        if (command == "int_counter"){
            ss >> counter_name;
            if (ss.fail()){
                throw MyExceptions::xMissingCounterName();
            }

            int ic_index = searchIntCounter(counter_name);
            int sc_index = searchStringCounter(counter_name);
            if (ic_index != -1){   // found int counter
                throw MyExceptions::xCounterAlreadyExists();
            }
            else if (sc_index != -1){   // found string counter
                throw MyExceptions::xCounterAlreadyExists();
            }
            else { // we need to create and add new counter, with given name, to list
                this->vecInt.push_back(Counter<int>(counter_name, INT));
            }
        }
        else if (command == "string_counter"){
            ss >> counter_name;
            if (ss.fail()){
                throw MyExceptions::xMissingCounterName();
            }

            int ic_index = searchIntCounter(counter_name);
            int sc_index = searchStringCounter(counter_name);
            if (ic_index != -1){   // found int counter
                throw MyExceptions::xCounterAlreadyExists();
            }
            else if (sc_index != -1){   // found string counter
                throw MyExceptions::xCounterAlreadyExists();
            }
            else { // we need to create and add new counter, with given name, to list
                this->vecStr.push_back(Counter<string>(counter_name, STR));
            }
        }
        else if (command == "add_from_file"){
            ss >> counter_name >> file_name;
            if (ss.fail()){
                throw MyExceptions::xMissingFileName();
            }
            ifstream in_file(file_name.c_str(), ios::in);
            if (!in_file.is_open()){
                throw MyExceptions::xFileFailure();
            }

            int ic_index = searchIntCounter(counter_name);
            int sc_index = searchStringCounter(counter_name);
            if (ic_index != -1){   // found int counter
                this->vecInt[ic_index].add_from_stream(in_file);
            }
            else if (sc_index != -1){   // found string counter
                this->vecStr[sc_index].add_from_stream(in_file);
            }
            else {  // counter doesn't exists
                throw MyExceptions::xCounterDoeasntExists(counter_name);
            }
        }
        else if (command == "add_from_string"){
            ss >> counter_name;

            int ic_index = searchIntCounter(counter_name);
            int sc_index = searchStringCounter(counter_name);
            if (ic_index != -1){   // found int counter
                this->vecInt[ic_index].add_from_stream(ss);
            }
            else if (sc_index != -1){   // found string counter
                this->vecStr[sc_index].add_from_stream(ss);
            }
            else {  // counter doesn't exists
                throw MyExceptions::xCounterDoeasntExists(counter_name);
            }
        }
        else if (command == "stats"){
            ss >> counter_name;
            if (ss.fail()){
                throw MyExceptions::xReadFailure();
            }

            int ic_index = searchIntCounter(counter_name);
            int sc_index = searchStringCounter(counter_name);
            if (ic_index != -1){   // found int counter
                this->vecInt[ic_index].print_to_stream(cout);
            }
            else if (sc_index != -1){   // found string counter
                this->vecStr[sc_index].print_to_stream(cout);
            }
            else {  // counter doesn't exists
                throw MyExceptions::xCounterDoeasntExists(counter_name);
            }
        }
        else if (command == "most_common"){
            ss >> counter_name;
            if (ss.fail()){
                throw MyExceptions::xReadFailure();
            }

            int ic_index = searchIntCounter(counter_name);
            int sc_index = searchStringCounter(counter_name);
            if (ic_index != -1){   // found int counter
                this->vecInt[ic_index].print_most_common(cout);
            }
            else if (sc_index != -1){   // found string counter
                this->vecStr[sc_index].print_most_common(cout);
            }
            else {  // counter doesn't exists
                throw MyExceptions::xCounterDoeasntExists(counter_name);
            }
        }
        else {
            throw MyExceptions::xUnknownCommand(command);
        }
    }
}

/*
 * The following counter-search methods look for counter by name
 * if found: return its index
 * if not found: return -1
 */
int Parser::searchIntCounter(const string& name){
    for (int i = 0; i < vecInt.size(); ++i) {
        if (vecInt[i].getId() == name){
            return i;
        }
    }
    return -1;
}
int Parser::searchStringCounter(const string& name){
    for (int i = 0; i < vecStr.size(); ++i) {
        if (vecStr[i].getId() == name){
            return i;
        }
    }
    return -1;
}