#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "Input.h"

class Arguments : public Input {
    public:
        Arguments() { }
        bool endOfLine() {
            if(cmd.at(cmd.size()-1) == ";") {
                return true;
            }
            return false;
        }
};

#endif