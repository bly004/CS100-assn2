#ifndef PROGRAM_H
#define PROGRAM_H

#include "Line.h"
#include "InputComposite.h"

class Program {
    protected:
        vector<Line* > lines;
        InputComposite* comp;
    public:
        Program() { }
        Line* createLine() {
            
        }
};

#endif