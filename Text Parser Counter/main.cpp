#include <iostream>
#include "Parser.h"

using namespace std;

int main() {

    Parser parser;
    try {
        parser.start();
    }
    catch (exception& e) {
        cerr << e.what() << endl;
        return -1;
    }
    catch (...) {
        cerr << "unknown error" << endl;
        return -1;
    }


    return 0;
}
