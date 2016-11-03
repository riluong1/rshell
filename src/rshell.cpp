#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <boost/tokenizer.hpp>
#include <sys/wait.h>
#include <sys/types.h>


using namespace boost;
using namespace std;
#define delimitor ";#"                    // token separators


bool runcmd (vector <char*> command) {
    command.push_back('\0'); 
    //appending the null character to the end of command
    int pid = fork();

    switch(pid) {
        case -1:
            perror ("Error in creating new process");
            exit(0);
            
        case 0:
            if (execvp(command[0], &command[0]) > 0) {
                //execvp used to link together files compiled by program
                return true;
            }
            else {
                perror ("Error in execvp");
                exit(1);
            }
            
        default:
            int current;
            if (waitpid(pid, &current, 0) == -1) {
                perror("Error in wait");
                return false;
            }
                if(current == 0)
                {

                        return true;

                }
            return false;
    }

    return false;
}


string getUserName (char *userName) {
    char hostName[1024];
    if(gethostname(hostName, sizeof hostName) == -1) {
    		perror("Cannot get Host Name");
         
    }

	if (getlogin() == NULL) {
	    perror("Cannot get User Name");
	    
    }

    else {}
    return hostName;
}


void commentCommand (vector <char*> &command, bool &comments) {
    comments = true;
    command.pop_back();
    runcmd(command);
    return;
}
void commandSemicolon(vector <char*> &command) {

            command.pop_back();
            runcmd(command);
            command.clear();
        return;
}
void commandAnd (vector <char*> &command, bool &previous) {


            command.pop_back();
            previous = runcmd(command);

            command.clear();
            return;
}
void commandOr (vector <char*> &command, bool &previous) {
    if (previous == false) {
        previous = true;
    }
                
    else {
        command.pop_back();
        previous = !runcmd(command);
    }
                
            
    command.clear();

    return;
}

typedef tokenizer<char_separator<char> > token;

int main(int argc, char **argv) {
    
    string commandString; 
    char *userName;

    vector <string> parse;
    vector <char*> command; 
    
    bool previous = true;
    bool comments = true;

    while (true) {
        
	    userName = getlogin();
	
        command.clear();
        parse.clear();
        previous = true;
        comments = false;
        
        
        cout << "$ ";
        getline(cin, commandString);
        char_separator<char> delim(" ", delimitor);
        tokenizer< char_separator<char> > token(commandString, delim);
       

        for (token::iterator it = token.begin(); it != token.end(); it++) { 
            parse.push_back(*it);
            
        }

        for (unsigned i = 0; i < parse.size(); i++) {
           command.push_back(const_cast<char*>(parse.at(i).c_str()));

            const char* temp = command.at(command.size() - 1);
            
            if (strcmp(command.at(command.size() - 1), "exit") == 0) { 
                exit(0);
            }
            
            else if (strcmp(command.at(command.size() - 1), "#") == 0) {
                commentCommand(command, comments);
            }
            else if (strcmp(command.at(command.size() - 1), ";") == 0) {
                
                commandSemicolon(command);

            }
            else if(strcmp(command.at(command.size() - 1), "&&") == 0) {
                
                commandAnd(command, previous);
                
            }
            
            else if (strcmp(command.at(command.size() - 1), "||") == 0) {
                commandOr(command, previous);
            }

        }
        
        
         if (command.size() >= 1 && previous && !comments) {
            runcmd(command);
        }
        
    
    }  
    
    return 0; 
}

