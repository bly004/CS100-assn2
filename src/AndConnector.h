#ifndef ANDCONNECTOR_H
#define ANDCONNECTOR_H

#include "Connectors.h"

class AndConnector : public Connectors {
    protected:
        bool executed;
    public:
        AndConnector() { }
        bool endOfLine() {
            return false; //not sure only if its impossible to end after an and
        }
};

#endif