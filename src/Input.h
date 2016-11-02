#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

class Input {
    protected:
        string cmd;
    public:
        Input() { }
        virtual bool endOfLine() = 0;
};

#endif