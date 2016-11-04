#ifndef EXECUTABLELINE2_H
#define EXECUTABLELINE2_H

#include <string>
#include <cstring>//strtok
#include <unistd.h>//fork, exec
#include <sys/types.h>//wait
#include <sys/wait.h>//wait
#include <stdio.h>//perror
#include <pwd.h>
#include <cstdlib>

using namespace std;

class ExecutableLine2 {
    protected:
        char* input;
        char* command[100];
        int size;
    public:
        ExecutableLine2() { }
        ExecutableLine2(char* in) {
            command[0] = in;
            command[1] = NULL;
        }
        void execute() {
            pid_t pid = fork();
            if(pid == -1) {
                perror("fork");
                exit(1);
            }
            if ( pid == 0 ) //child
            {
                if ( execvp ( command[0], command) == -1 )//args[0]
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
        void print() {
            cout << command[0] << endl;
        }
};
#endif