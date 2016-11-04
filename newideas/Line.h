#ifndef LINE_H
#define LINE_H

//#include "Input.h"
#include <iostream>
#include <climits>
#include <cstring>//strtok
#include <vector>
#include "ExecutableLine2.h"

using namespace std;

class Line {
    protected:
        vector<ExecutableLine2*> list;
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
            list.push_back(new ExecutableLine2(line[0]));
            int i = 1;
            while( line[ i - 1 ] != NULL )
            {
                line[i] = strtok( NULL , ";" );
                //char* temp = strtok( NULL, ";" );
                list.push_back(new ExecutableLine2(line[i]));
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
            cout << endl;
            for(int i = 0; i < list.size(); i++) {
                list.at(i)->print();
            }
            cout << endl;
        }
        void execute() {
            for(int i = 0; i < list.size(); i++) {
                list.at(i)->execute();
                cout << "err" << endl;
            }
        }
};

#endif