#include <iostream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <cstdlib>

using namespace std;
using namespace boost;

bool execute(string);
bool test(string);
bool run(string);

int main(int argc, char** argv) {
    //finding user login info
    string user, info;
    
    char hostInfo[256];
    struct passwd *u = getpwuid(getuid());
    int h = gethostname(hostInfo, 256);
    
    if(u != 0 && h != -1) {
        user = u->pw_name;
        info = hostInfo;
        info.append("@");
        info.append(user);
        info.append("$ ");
    } else {
        info = "user@host_name$ ";
    }
    //string input = "";
    /*for(int i = 1; i < argc; i++) {//comment out if using user input
        input += argv[i];//comment out if using user input
    }//comment out for user input
    cout << "$ " << input << endl;*/
    while(1) {//use this for user input
        string input = "";
        cout << info;//use this for user input
        getline(cin, input);//use this for user input instead of command line
        typedef tokenizer<char_separator<char> > tokenizer;
        char_separator<char> sep(";");
        tokenizer tkn(input, sep);
        for(tokenizer::iterator tok = tkn.begin(); tok != tkn.end(); tok++) {
            string currTok = *tok;
            if(currTok.find("&") != string::npos) { //else if
                bool passed = true;
                char_separator<char> sep1("&");
                tokenizer tkn1(currTok, sep1);
                for(tokenizer::iterator tok1 = tkn1.begin(); tok1 != tkn1.end(); tok1++) {
                    if(passed == true) {
                        string temp_and = *tok1;
                        if(temp_and.find("exit") != string::npos) {
                            return 1;
                        }
                        passed = run(temp_and);
                    }
                }
            } else if(currTok.find("|") != string::npos) {
                bool passed = false;
                char_separator<char> sep2("|");
                tokenizer tkn2(currTok, sep2);
                for(tokenizer::iterator tok2 = tkn2.begin(); tok2 != tkn2.end(); tok2++) {
                    if(passed == false) {
                        string temp_or = *tok2;
                        if(temp_or.find("exit") != string::npos) {
                            return 1;
                        }
                        passed = run(temp_or);
                    }
                }
            } else {
                if(currTok == "exit") { //|| currTok.find("exit") != string::npos) {
                    return 1;
                }
                run(currTok);
            }
        }
    }
}

bool run(string temp) {
    bool ret;
    string temp2 = temp;
    if( temp2.find("test") != string::npos ) {
        while(temp2.at(temp2.size() - 1) == ' ') {
            temp2 = temp2.substr(0, temp2.size() - 1);
        }
        ret = test(temp2);
    } else if( temp2.find("[") != string::npos && temp2.find("]") != string::npos ) {
        temp2 = temp2.substr(0, temp2.find("]") - 1);
        ret = test(temp2);
    } else {
        while(temp2.at(temp2.size() - 1) == ' ') {
            temp2 = temp2.substr(0, temp2.size() - 1);
        }
        ret = execute(temp2);
    }
    return ret;
}

bool execute(string temp) {
    bool ret = true;
    pid_t pid;
    typedef tokenizer<char_separator<char> > tokenizer;
    char **ptr;
    string temp1 = temp;
    vector<char *> v;
    while(temp1.find(" ") == 0) {
        temp1.erase(0,1);
    }
    if(temp1.find("#") != string::npos) {
        int index = temp1.find("#");
        temp1 = temp1.substr(0, index);
    }
    if(temp1.find(" ") != string::npos) {
        int i = 0;
        string temp_last;
        char_separator<char> sep_2(" ");
        tokenizer tkn_2(temp1, sep_2);
        for(tokenizer::iterator tok_2 = tkn_2.begin(); tok_2 != tkn_2.end(); tok_2++) {
            string temp_2 = *tok_2;
            char *temp_1 = new char[temp_2.size()];
            copy(temp_2.begin(), temp_2.end(), temp_1);
            v.push_back(temp_1);
            i++;
            temp_last = temp_2;
        }
        //v.push_back('\0');
        char *temp_3 = new char[temp_last.size() + 1];
        copy(temp_last.begin(), temp_last.end(), temp_3);
        temp_3[temp_last.size()] = '\0';
        v.pop_back();
        v.push_back(temp_3);
        ptr = &v[0];
    } else {
        char *temp_1 = new char[temp1.size() + 1];
        copy(temp1.begin(), temp1.end(), temp_1);
        temp_1[temp1.size()] = '\0';
        v.push_back(temp_1);
        ptr = &v[0];
    }
    pid = fork();
    if(pid == -1) {
        return false;
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
    return ret;
}

bool test(string temp) {
    struct stat buf;
    if(temp.find("-e") != string::npos) {
        string temp2 = temp.substr(temp.find("-e") + 3);
        if(stat(temp2.c_str(), &buf) == 0) {
            cout << "(TRUE)" << endl;
            return true;
        } else {
            cout << "(FALSE)" << endl;
            return false;
        }
    }
    if(temp.find("-f") != string::npos) {
        string temp2 = temp.substr(temp.find("-f") + 3);
        if(stat(temp2.c_str(), &buf) == 0) {
            if(S_ISREG(buf.st_mode)) {
                cout << "(TRUE)" << endl;
                return true;
            } else {
                cout << "(FALSE)" << endl;
                return false;
            }
        } else {
            cout << "(FALSE)" << endl;
            return false;
        }
    }
    if(temp.find("-d") != string::npos) {
        string temp2 = temp.substr(temp.find("-d") + 3);
        if(stat(temp2.c_str(), &buf) == 0) {
            if(S_ISDIR(buf.st_mode)) {
                cout << "(TRUE)" << endl;
                return true;
            } else {
                cout << "(FALSE)" << endl;
                return false;
            }
        } else {
            cout << "(FALSE)" << endl;
            return false;
        }
    }
    if(temp.find("-e") == string::npos && temp.find("-f") == string::npos && temp.find("-d") == string::npos) {
        string temp2 = temp;
        if(temp2.find("[") != string::npos) {
            temp2 = temp2.substr(temp2.find("[") + 2);
        }
        if(temp2.find("test") != string::npos) {
            temp2 = temp2.substr(temp2.find("test") + 5);
        }
        if(stat(temp2.c_str(), &buf) == 0) {
            cout << "(TRUE)" << endl;
            return true;
        } else {
            cout << "(FALSE)" << endl;
            return false;
        }
    }
}