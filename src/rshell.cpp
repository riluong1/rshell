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
#include <sys/stat.h>


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

bool runTest(vector <char*> command)
{
    command.pop_back();
    
    

if (command.size() == 1) 
{
    cout << "(False)\n";
    return false;
}

    const char* NAME_OF_PATH = command.at(command.size() - 1);
    const char* flag = command.at(command.size() - 2);
    struct stat sb;
    int fileinfo = stat(NAME_OF_PATH, &sb);
    
   
    
    if (strcmp(command.at(command.size() - 2), "test") == 0) 
    {
        if (fileinfo == 0)
        {
            cout << "(True)\n";
            return true; 
        }
        cout << "(False)\n";
        return false;
    }
        else if (strcmp(flag, "-e") == 0 || strcmp(flag, "[") == 0)
    {
        if (fileinfo == 0)
        {
            cout << "(True)\n";
            return true; 
        }
        cout << "(False)\n";
        return false;
    }
    
    else if (strcmp(flag, "-f") == 0)
    { 
        if (S_ISREG(sb.st_mode)) 
        {
             cout << "(True)\n";
             return true;
        }
        cout << "(False)\n";
        return false;
    }
    
    else if (strcmp(flag, "-d") == 0)
    {
        if (S_ISDIR(sb.st_mode))
        {
            cout << "(True)\n";
            return true;
        }
        cout << "(False)\n";
        return false;
    }  

 else 
    {
        cout << flag << "unary operator expected" << endl;
        
        return false;
    }
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
void autorun(vector <char *> &command, bool &comments, bool &previous, bool &isTest) {
    if (command.size() >= 1 && previous && !comments) {
      
        if (!isTest) {
            runcmd(command);
        }
        else {
            
            command.push_back('\0');
            
         
            runTest(command);
            
        }
        //even though there may be no comments/connectors,
        //we still need to exec the command 
    }
    return;
  //does nothing if it has comments (#) or is a connector command
}

typedef tokenizer<char_separator<char> > token;

int main(int argc, char **argv) {
    
    string commandString; 
    char *userName;

    vector <string> parse;
    vector <char*> command; 
    
    bool previous = true;
    bool comments = true;
    bool isTest = true;

    while (true) {
        
	    userName = getlogin();
	
        command.clear();
        parse.clear();
        previous = true;
        comments = false;
        
        
        //cout << userName << "@" << (getUserName(userName)) <<  "$ ";
        cout << "$ ";
        getline(cin, commandString);

        char_separator<char> delim(" ", delimitor);
        tokenizer< char_separator<char> > token(commandString, delim);
       

        for (token::iterator it = token.begin(); it != token.end(); it++) { 
            parse.push_back(*it);
            
        }

        for (unsigned i = 0; i < parse.size(); i++) {
           command.push_back(const_cast<char*>(parse.at(i).c_str()));

           
            
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
            else if (strcmp(command.at(command.size() - 1), "test") == 0) {
                
                isTest = true;
                	
            }
            
            else if (strcmp(command.at(command.size() - 1), "||") == 0) {
                commandOr(command, previous);
            }
	    
		else if (strcmp(command.at(command.size() - 1), "[") == 0) {
                
                isTest = true;
            }
            
            else if (strcmp(command.at(command.size() - 1), "]") == 0){
            
                //delete ending symbolic bracket
                command.pop_back();
            }

        }
        
        
        autorun(command, comments, previous, isTest);
        // new autorun function accommodates to the Test run execution
        
        
    
    }  
    
    return 0; 
}


