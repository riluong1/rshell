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
#define delimitor ";#()"                    // token separators


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

void CDcommand( vector<string> command)
{
    int num;
    cout << command.size();
    if (command.size() == 1)
    {
        num = chdir(getenv("HOME"));
        
        if (num == -1)
        {
            perror("error with cd");
        }
    }
    // else if(strcmp(command.at(command.size() - 1), "-") == 0))
    // {
        num = chdir(setenv)
    // }
        else
        {
            num = chdir(command.at(command.size() - 1).c_str());
            if (num == -1)
            {
                perror("error with cd");
            }
        }
    
    
    return;
}
bool runTest(vector <char*> command)
{
    //pops null character
    command.pop_back();
    
    
//checks for just test without any flags or any parameters
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
            cout << "(True)\n";  //prints true if it exist
            return true; 
        }
        cout << "(False)\n"; //prints false if it does not exist
        return false;
    }
        else if (strcmp(flag, "-e") == 0 || strcmp(flag, "[") == 0)
    {
        if (fileinfo == 0)
        {
            cout << "(True)\n";  //prints true if it exist 
            return true; 
        }
        cout << "(False)\n";   //prints false if it does not exist
        return false;
    }
    
    else if (strcmp(flag, "-f") == 0)
    { 
        if (S_ISREG(sb.st_mode)) 
        {
             cout << "(True)\n";  //prints true if it exist and is a file
             return true;
        }
        cout << "(False)\n";  //prints false if it exist and is not a file
        return false;
    }
    
    else if (strcmp(flag, "-d") == 0)
    {
        if (S_ISDIR(sb.st_mode))
        {
            cout << "(True)\n";  //prints true if it exist and is a directory
            return true;
        }
        cout << "(False)\n";   //prints true if it exist and is not a directory
        return false;
    }  

 else 
    {
        cout << flag << " unary operator expected" << endl;  //prints error if invalid flag is passed in
        
        return false;
    }
}

void TestConnectorCheck(vector <char*> &command, bool &previous, bool &firstfail, bool &isTest, bool &tested, const char* temp) {
    
    // Will check for connectors with test 
    
    //Or command checker with test
    if(previous == true)
            {
                if (strcmp(temp, "||") == 0)
                {
                    previous = !runTest(command);  //checks if the command failed
                    firstfail = true;
                }
                else
                {
                    previous = runTest(command); //runs the command if the first comamnd did not fail
                }
            }
          

            if(firstfail)
            {
                firstfail = false;
                previous = true;
            }
            isTest = false;
            command.clear();  //clears it
            tested = true;
        return;
}


string getUserName (char *userName) {
    char hostName[1024];
    if(gethostname(hostName, sizeof hostName) == -1) {
    		perror("Cannot get Host Name");
         
    }

	if (getlogin() == NULL) {
	    perror("Cannot get User Name");
	    
    }

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
void autorun(vector <char *> &command, bool &comments, bool &previous, bool &isTest, vector <string> parsed) {
    if (command.size() == 1 && previous && !comments) {
      
        if (isTest) {
            
            command.push_back('\0');
            runTest(command);
        }
        else if (strcmp(command.at(command.size() - 1), "cd") == 0 )
        {
            // command.push_back('\0');
            CDcommand(parsed);
        }
        else {
            
            runcmd(command);
            
        }
        //even though there may be no comments/connectors,
        //we still need to exec the command 
    }
    return;
  //does nothing if it has comments (#) or is a connector command
}

void frontParanthesis (vector <char *> &command, bool &previous, bool &falseP) {
	if (previous == false)
        {

                falseP = true;

        }
        else if (previous == true)
        {

                command.pop_back(); 
        }
    return;
}
void backParanthesis (vector <char *> &command, bool &previous, bool &falseP) {

	 if (falseP == true)
            {
                
                falseP = false;
                //clear cmnd 
                command.clear();

            }
            else if (falseP == false)
            {
                command.pop_back();
            }

}

void correctPar(bool &parError, int &LeftPar, int &RightPar) {
	
	//if there are an equal number of () then it ignores it
	//manually outputting error if needed
	if (RightPar > LeftPar) {
	   cout << "syntax error near unexpected token (" << endl;
	   parError = true;
    }
	else if (LeftPar > RightPar) {
	   cout << "syntax error near unexpected token (" << endl;
	   parError = true;
	}
	else
	{
	    return;
	}
	
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
    bool isTest = false;
    bool tested = false;
    bool parError = false;
    bool falseP = false;
    bool firstfail = false;
    
    int LeftPar = 0;
    int RightPar = 0;

    while (true) {
        
	    userName = getlogin();
	
        command.clear();
        parse.clear();
        previous = true;
        comments = false;
        tested = false;
        parError = false;
        firstfail = false;
        isTest = false;
        falseP = false;
        LeftPar = 0;
        RightPar = 0;
        
        //cout << userName << "@" << (getUserName(userName)) <<  "$ ";
        char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("Printing current directory error");
		}
	    else 
		{
			cout<< cwd << endl;
		}
        
        cout << "$ ";
        getline(cin, commandString);

        char_separator<char> delim(" ", delimitor);
        tokenizer< char_separator<char> > token(commandString, delim);
       

        for (token::iterator it = token.begin(); it != token.end(); it++) { 
            
            parse.push_back(*it);
            
            //parentheses check, if equal amount then its valid
            if (*it == "(") { 
                   
                   LeftPar++;
               }
               else if (*it == ")") {
                   
                   RightPar++;
               }
            
        }
        
        correctPar(parError, LeftPar, RightPar); //parentheses have to be equal amount or else the input is invalid

        for (unsigned i = 0; i < parse.size(); i++) {
           command.push_back(const_cast<char*>(parse.at(i).c_str()));
           
            tested = false;

            const char* temp = command.at(command.size() - 1);
           
            if (isTest == true) {
                if (strcmp(temp, "&&") == 0) {
                    TestConnectorCheck(command, previous, firstfail, isTest, tested, temp);
                }
                
                else if (strcmp(temp, "||") == 0) {
                   TestConnectorCheck(command, previous, firstfail, isTest, tested, temp);
                }
                
                else if (strcmp(temp, ";") == 0) {
                    TestConnectorCheck(command, previous, firstfail, isTest, tested, temp);
                }
            }

           
            
            if (strcmp(command.at(command.size() - 1), "exit") == 0) { //checks if exit is passed in
                exit(0);
            }
            
            else if (strcmp(command.at(command.size() - 1), "#") == 0) { //check if # passed in
                commentCommand(command, comments);
            }
            else if (strcmp(command.at(command.size() - 1), ";") == 0) {  //check if ; passed in
                
                commandSemicolon(command);

            }
            else if(strcmp(command.at(command.size() - 1), "&&") == 0) { //check if && used
                
                commandAnd(command, previous);
                
            }
            else if(strcmp(command.at(command.size() - 1), "cd") == 0 ) {
                
                CDcommand(parse);
            }
            else if (strcmp(command.at(command.size() - 1), "test") == 0) { //check if test used
                
                isTest = true;
                	
            }
            
            else if (strcmp(command.at(command.size() - 1), "||") == 0) { //check if || used
                
                commandOr(command, previous);
            }
            
            else if (strcmp(command.at(command.size() - 1), "[") == 0) { //check if [ passed in
                
                isTest = true;
            }
            
            else if (strcmp(command.at(command.size() - 1), "]") == 0){ //check if ] passed in
            
                //delete it and do nothing
                command.pop_back();
            }
            else if (strcmp(command.at(command.size() - 1), "(") == 0) { //check if ( passed in
            	
            	frontParanthesis(command, previous, falseP);
            }
        
            else if (strcmp(command.at(command.size() - 1), ")") == 0) { //check if ) passed in
            	
            	backParanthesis(command, previous, falseP);
            }
            else if(parError)
            {
                previous = false;
            }

        }
        
        
        autorun(command, comments, previous, isTest, parse); //executes command
        
    }  
    
    return 0; 
}


