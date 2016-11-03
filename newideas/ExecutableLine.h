#ifndef EXECUTABLELINE_H
#define EXECUTABLELINE_H

//#include "Input.h"
#include <climits>
#include <cstring>//strtok

using namespace std;

class ExecutableLine {
    protected:
        Line* line;
        char** command;
        int size;
    public:
        ExecutableLine() { }
        ExecutableLine(Line* in) {
            line = in;
            size = 0;
            parse();
        }
        void parse() {
            command[0] = strtok( command , " " );
            int i = 1;
            while( command[ i - 1 ] != NULL )
            {
                command[i] = strtok( NULL , ";" );
                i++;
            }
            command[ i - 1] = NULL;
            size = i;
        }
        int getSize() {
            return size;
        }
};

#endif