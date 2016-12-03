# rshell

<h1> Program Basics 

This rshell program simulates the bash executables and the Unix interpreter command line, written in C++. With this program, we are able to execute simple commands such as ls, echo, mkdir, etc with connectors. The purpose of the shell command line is to read, interpret, and execute commands. Rshell also has the test operator and precedence operator.





<h2>**Current Bugs:

- The exit command does not follow the rules of the connector. The exit command exits regardless if the first test fails or succeeds using the OR connector, and the exit command also exits regardless of the AND connector.

- For the AND connector, if the first command the second command are false, a semicolon followed by a command will not execute.

- Some chains of commands produce incorrect input specifically involving the AND and OR connectors.

- When using the precedence operator, if a ( or ) is missing, rshell will not wait for a finishing or starting parentheses. It will print out an error message.

- CD only works if you use it by itself. Chaining CD with other commands will cause it to fail.

- Once you use CD, our program no longer can no longer create files or directories.

- If the getusername function fails, the current directory we are in will not print.
