#ifndef LINE_H
#define LINE_H

#include "Executables.h"
#include "Arguments.h"
#include "Connectors.h"

class Line {
    protected:
        Executables* exec;
        vector<Arguments* > args;
        Connector* connect
    public:
        Line() { }
        void execute() {
            
        }
};

#endif