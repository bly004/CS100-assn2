#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class Input {
    protected:
        char* input;
    public:
        Input() { }
        Input(char* in) {
            input = in;
            //p
        }
};

#endif