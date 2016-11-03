#ifndef ORCONNECTOR_H
#define ORCONNECTOR_H

#include "Connectors.h"

class OrConnector : public Connectors {
    protected:
        bool executed;
    public:
        OrConnector() { }
        bool endOfLine() {
            return false; //not sure only if its impossible to end after an or
        }
};

#endif