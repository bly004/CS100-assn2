/*
#include "AndConnector.h"
#include "Arguments.h"
#include "Connectors.h"
#include "Executables.h"
#include "Input.h"
#include "InputComposite.h"
#include "Line.h"
#include "OrConnector.h"
#include "Program.h"
*/
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


using namespace std;


int main() {
    
    //finding user login info
    string user, info;
    
    char hostInfo[256];
    struct passwd *u = getpwuid(getuid());
    int h = gethostname(hostInfo, 256);
    
    if(u != 0 && h != -1) {
        user = u->pw_name;
        //info = hostInfo + "@" + user + "$ ";
        info = hostInfo;
        info.append("@");
        info.append(user);
        info.append("$");
    } else {
        info = "user@host_name$ ";
    }
    ////////////////////
    //read input in from test file, fill str with it
    char str[1000000];
    //read from tests
        //ifstream inFS;
        //inFS.open( "tests.txt");
        //inFS.getline(args, 10000000, '\0');
        
    cin.getline( str, 100 );//replace with test input somehow
    char* cmd[1000];//any size?
    cmd[0] = strtok( str , ";" );
    int i = 1;
    while( cmd[ i - 1 ] != NULL )
    {
        cmd[i] = strtok( NULL , ";" );
        i++;
    }
    /*int z = 0;
    while(cmd[z] != NULL) {
        cout << cmd[z] << endl;
        z++;
    }*/
    //get user input
    //string ls = "ls";
    char* args[ i - 1 ];//fill with real size
    for(int y = 0; y < i - 1; ++y)
    {
        args[y] = cmd[y];
        cout << args[y] << endl;
    }
    //args[0] = (char*)ls.c_str(); //fill with actual input
    args[ i - 1 ] = NULL;//execvp needs this null to run correctly
    
    /*if ( execvp ( args[0], args) == -1 )
    {
        perror ( "exec" );
    }*/
    
    for(int y = 0; y < i; ++y)
    {
    
    pid_t pid = fork();
    
    if(pid == -1) {
        perror("fork");
        exit(1);
    }
    if ( pid == 0 ) //child
    {
        if ( execvp ( args[y], args) == -1 )//args[0]
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
        //cout << "end inside parent?" << endl;
    }
    
    }
    //cout << "end?" << endl;
    
    //cout << info << endl;
    
    return 0;
}