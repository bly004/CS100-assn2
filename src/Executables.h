#ifndef EXECUTABLES_H
#define EXECUTABLES_H

#include "Input.h"

class Executables : public Input {
    protected:
        int numArguments;
    public:
        Executables() { }
        bool endOfLine() {
            if(cmd.at(cmd.size()-1) == ";") {
                return true;
            }
            return false;
        }
};

#endif