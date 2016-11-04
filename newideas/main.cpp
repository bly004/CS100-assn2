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

    char str[100000];
    cin.getline( str, 100 );
    
    Line* line = new Line(str);
    line->print();
    line->execute();

    
    return 0;
}