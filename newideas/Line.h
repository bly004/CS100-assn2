#ifndef LINE_H
#define LINE_H

//#include "Input.h"
#include <iostream>
#include <climits>
#include <cstring>//strtok

using namespace std;

class Line {
    protected:
        char* input;
        char* line[100];
        int size;
    public:
        Line() { }
        Line(char* in) {
            input = in;
            size = 0;
            parse();
        }
        void parse() {
            line[0] = strtok( input , ";" );//line
            int i = 1;
            while( line[ i - 1 ] != NULL )
            {
                line[i] = strtok( NULL , ";" );
                i++;
            }
            size = i - 1;
        }
        int getSize() {
            return size;
        }
        char* get(int index) {
            return line[index];
        }
        void print() {
            for(int i = 0; i < size; i++) {
                cout << line[i] << endl;
            }
        }
};

#endif