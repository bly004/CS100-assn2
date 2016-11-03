#include "Line.h"
#include "ExecutableLine.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>//fork, exec
#include <pwd.h>
#include <sys/types.h>//wait
#include <sys/wait.h>//wait
#include <fstream>
#include <stdio.h>//perror
#include <cstring>//strtok
#include <climits>

using namespace std;


int main() {

    char* str;
    
    cin.getline( str, 100 );
    Line* line(in);
    ExecutableLine* exLine( line );

    for(int i = 0; i < exLine.size(); ++i) {
        if(pid == -1) {
            perror("fork");
            exit(1);
        }
        if ( pid == 0 ) //child
        {
            if ( execvp ( args[i], args) == -1 )//args[0]
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

    
    return 0;
}