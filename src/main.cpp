#include <iostream>
#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <cstdlib>

using namespace std;
using namespace boost;

bool execute(string);
bool test(string);
bool run(string);
bool dir(string);
string pwd = "";
string oldpwd = "";

int main(int argc, char** argv) {
    //string input = "";
    /*for(int i = 1; i < argc; i++) {//comment out if using user input
        input += argv[i];//comment out if using user input
    }//comment out for user input
    cout << "$ " << input << endl;*/
    //pid_t pid;
    pwd = getenv("PWD");
    while(1) {//use this for user input
        string input = "";
        //cout << "$ ";//use this for user input
        cout << getenv("PWD") << " ";
        //cout << pwd << " ";
        getline(cin, input);//use this for user input instead of command line
        typedef tokenizer<char_separator<char> > tokenizer;
        char_separator<char> sep(";");
        tokenizer tkn(input, sep);
        for(tokenizer::iterator tok = tkn.begin(); tok != tkn.end(); tok++) {
            string currTok = *tok;
            /*if(currTok.find("&") != string::npos && currTok.find("|") != string::npos) {
                bool lPass;
                bool inP;
                bool pVal;
                bool inA;
                char_seperator<char> sep4("", "|&()", boost::keep_empty_tokens);
                tokenizer tkn4(currTok, sep4);
                for(tokenizer::iterator tok4 = tkn4.begin(), tok4 != tkn4.end(); tok4++) {
                    if(*tok == "(") {
                        inP = true;
                        continue;
                    }
                    if(*tok == ")") {
                        inP = false;
                        pVal = lPass;
                        continue;
                    }
                    if(*tok == "|") {
                        inA = false;
                        continue;
                    }
                    if(*tok == "&") {
                        inA = true;
                        continue;
                    }
                    if(tok4 == tkn4.begin()) {
                        lPass = run(*tok4);
                        continue;
                    }
                    if(lPass && !inA) {
                        lPass = true;
                        continue;
                    }
                    if(!lPass && !inA) {
                        lPass = run(*tok4);
                    }
                    if(lPass && inA) {
                        lPass = run(*tok4);
                    }
                    if(!lPass && inA) {
                        lPass = false;
                    }
                }
            }*/
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
    while(temp2.at(0) == ' ') {//changed
            temp2 = temp2.substr(1);
    }
    while(temp2.at(temp2.size() - 1) == ' ') {//changed
            temp2 = temp2.substr(0, temp2.size() - 1);
    }
    if( temp2.find("test") != string::npos && temp2.find("tests") == string::npos ) {
        /*while(temp2.at(temp2.size() - 1) == ' ') {//changed
            temp2 = temp2.substr(0, temp2.size() - 1);
        }*/
        ret = test(temp2);
    } else if( temp2.find("[") != string::npos && temp2.find("]") != string::npos ) {
        temp2 = temp2.substr(0, temp2.find("]") - 1);
        ret = test(temp2);
    } else if(temp2.find("cd") != string::npos) {
        ret = dir(temp2);
    } else {
        /*while(temp2.at(temp2.size() - 1) == ' ') {//changed
            temp2 = temp2.substr(0, temp2.size() - 1);
        }*/
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
            temp_1[temp_2.size()] = '\0';//new added
            v.push_back(temp_1);
            i++;
            temp_last = temp_2;
            temp_1 = NULL;//new added
            delete temp_1;//new added
        }
        //v.push_back('\0');
        char *temp_3 = new char[temp_last.size() + 1];
        copy(temp_last.begin(), temp_last.end(), temp_3);
        temp_3[temp_last.size()] = '\0';
        v.pop_back();
        v.push_back(temp_3);
        ptr = &v[0];
        temp_3 = NULL;//new added
        delete temp_3;//new added
    } else {
        char *temp_1 = new char[temp1.size() + 1];
        copy(temp1.begin(), temp1.end(), temp_1);
        temp_1[temp1.size()] = '\0';
        v.push_back(temp_1);
        ptr = &v[0];
        temp_1 = NULL;//new added
        delete temp_1;//new added
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

bool dir(string temp) {
    if(temp.find("cd -") != string::npos) {
        char* temp1 = getenv("OLDPWD");
        if(temp1 == NULL) {
            perror("getenv");
            return false;
        }
        if(-1 == setenv("OLDPWD", getenv("PWD"), 1) ) {
            perror("setenv");
            return false;
        } else {
            oldpwd = getenv("OLDPWD");
        }
        if(-1 == setenv("PWD", temp1, 1) ) {
            perror("setenv");
            return false;
        } else {
            pwd = getenv("PWD");
            chdir(pwd.c_str());
        }
        return true;
    } else if(temp == "cd") {
        char* temp1 = getenv("HOME");
        if(temp1 == NULL) {
            perror("getenv");
            return false;
        }
        if(-1 == setenv("OLDPWD", getenv("PWD"), 1) ) {
            perror("setenv");
            return false;
        } else {
            oldpwd = getenv("OLDPWD");
        }
        if(-1 == setenv("PWD", temp1, 1) ) {
            perror("setenv");
            return false;
        } else {
            pwd = getenv("PWD");
            chdir(pwd.c_str());
        }
        return true;
    } else {
        string temp1 = temp.substr(temp.find("cd") + 3);
        temp1 = "/" + temp1;
        char* temp2 = getenv("PWD");
        temp1 = temp2 + temp1;
        temp2 = &temp1[0];
        /*if(temp2 == NULL) {
            perror("getenv");
            cout << "error end else" << endl;
            return false;
        }*/
        char* temp3 = getenv("OLDPWD");
        char* temp4 = getenv("PWD");
        if(-1 == setenv("OLDPWD", getenv("PWD"), 1) ) {
            perror("setenv");
            return false;
        } else {
            oldpwd = getenv("OLDPWD");
        }
        if(-1 == setenv("PWD", temp2, 1) ) {
            perror("setenv");
            setenv("OLDPWD", temp3, 1);
            oldpwd = getenv("OLDPWD");
            return false;
        } else {
            if( chdir(getenv("PWD")/*pwd.c_str()*/) == -1 ) {
                perror("chdir");
                setenv("OLDPWD", temp3, 1);
                oldpwd = getenv("OLDPWD");
                setenv("PWD", temp4, 1);
                pwd = getenv("PWD");
                return false;
            }
            pwd = getenv("PWD");
            //chdir(pwd.c_str());
        }
        return true;
    }
}

//execute(*tok);
                /*string temp = *tok;
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
                v.clear();*/
            //}