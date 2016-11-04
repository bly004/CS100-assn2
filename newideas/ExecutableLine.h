#ifndef EXECUTABLELINE_H
#define EXECUTABLELINE_H

//#include "Input.h"
#include <climits>
#include <cstring>//strtok
#include <unistd.h>//fork, exec
#include <sys/types.h>//wait
#include <sys/wait.h>//wait
#include <stdio.h>//perror
#include <pwd.h>
#include <cstdlib>
#include <string>

using namespace std;

class ExecutableLine {
    protected:
        char* input;
        Line* line;
        char* command[100];
        int size;
    public:
        ExecutableLine() { }
        ExecutableLine(Line* in) {
            line = in;
            size = 0;
            parse();
        }
        void parse() {
            string temp;
            if(line->getSize() > 0) {
                temp = line->get(0);
            }
            for(int i = 1; i < line->getSize(); i++) {
                temp += line->get(i);
            }
            //cout << "temp" << temp << endl;
            command[temp.size()] = NULL;
            memcpy(input, temp.c_str(), temp.size());
            cout << "input" << input[0] << endl;
            command[0] = strtok( input , " " );//command
            int i = 1;
            while( command[ i - 1 ] != NULL )
            {
                command[i] = strtok( NULL , ";" );
                i++;
            }
            command[ i - 1] = NULL;
            size = i;
            cout << "size of i: " << i << endl;
        }
        int getSize() {
            return size;
        }
        void execute() {
            for(int i = 0; i < size; ++i) {
                pid_t pid = fork();
                if(pid == -1) {
                    perror("fork");
                    exit(1);
                }
                if ( pid == 0 ) //child
                {
                    if ( execvp ( command[i], command) == -1 )//args[0]
                    {
                        perror ( "exec" );
                        exit(1);
                    }
                }
                if ( pid > 0 ) //parent
                {
                    if ( wait(0) == -1 ) {
                        perror ( "wait" );
                        exit(1);
                    }
                }
            }
        }
};

#endif