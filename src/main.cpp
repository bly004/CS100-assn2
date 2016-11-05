#include <iostream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <cstdlib>

using namespace std;
using namespace boost;

int main(int argc, char** argv) {
    string input = "";
    /*for(int i = 1; i < argc; i++) {//comment out if using user input
        input += argv[i];//comment out if using user input
    }*///comment out for user input
    //cout << "$ " << input << endl;
    pid_t pid;
    while(1) {//use this for user input
        cout << "$ ";//use this for user input
        getline(cin, input);//use this for user input instead of command line
        typedef tokenizer<char_separator<char> > tokenizer;
        char_separator<char> sep(";");
        tokenizer tkn(input, sep);
        for(tokenizer::iterator tok = tkn.begin(); tok != tkn.end(); tok++) {
            char **ptr;
            vector<char *> v;
            if(v.empty() && (tok->compare("exit") == 0)) {
                return 1;
            }
            if((tok->compare("&") == 0) && (tok->compare("|") == 0)) {
                
            } else if(tok->compare("&") == 0) {
                
            } else if(tok->compare("|") == 0) {
                
            } else {
                string temp = *tok;
                if(temp.find(" ") == 0) {
                    temp.erase(0,1);
                }
                if(temp.find("#") != string::npos) {
                    int index = temp.find("#");
                    temp = temp.substr(0, index);
                }
                if(temp.find(" ") != string::npos) {
                    char_separator<char> sep_2(" ");
                    tokenizer tkn_2(temp, sep_2);
                    for(tokenizer::iterator tok_2 = tkn_2.begin(); tok_2 != tkn_2.end(); tok_2++) {
                        string temp_2 = *tok_2;
                        char *temp_1 = new char[temp_2.size()];
                        copy(temp_2.begin(), temp_2.end(), temp_1);
                        v.push_back(temp_1);
                    }
                    v.push_back('\0');
                    ptr = &v[0];
                } else {
                    char *temp_1 = new char[temp.size() + 1];
                    copy(temp.begin(), temp.end(), temp_1);
                    temp_1[temp.size()] = '\0';
                    v.push_back(temp_1);
                    ptr = &v[0];
                }
                pid = fork();
                if(pid == -1) {
                    return -1;
                }
                if(pid == 0) {
                    if(execvp(ptr[0], ptr) == -1) {
                        perror("Execvp Failed");
                    }
                    exit(1);
                }
                if(pid > 0) {
                    if(wait(0) == -1) {
                        perror("Wait");
                        exit(1);
                    }
                }
                ptr = NULL;
                v.clear();
            }
        }
    }
}