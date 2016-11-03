#ifndef LINE_H
#define LINE_H

//#include "Input.h"
#include <climits>
#include <cstring>//strtok

using namespace std;

class Line {
    protected:
        char* input;
        char** line;
        int size;
    public:
        Line() { }
        Line(char* in) {
            input = in;
            size = 0;
            parse();
        }
        void parse() {
            line[0] = strtok( line , ";" );
            int i = 1;
            while( line[ i - 1 ] != NULL )
            {
                line[i] = strtok( NULL , ";" );
                i++;
            }
            size = i - 1;
        }
};

#endif