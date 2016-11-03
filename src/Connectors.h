#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "Input.h"

class Connectors : public Input {
    public:
        Connectors() { }
        bool endOfLine() {
            if(cmd.at(cmd.size()-1) == ";") {
                return true;
            }
            return false;
        }
};

#endif