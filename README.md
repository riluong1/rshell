# rshell

**Program Basics <h1>

This rshell program simulates the bash executables and the Unix interpreter command line, written in C++. With this program, we are able to execute simple commands such as ls, echo, mkdir, etc. The purpose of the shell command line is to read, interpret, and execute commands.





**Current Bugs: <h2>

- The exit command does not follow the rules of the connector. The exit command exits regardless if the first test fails or succeeds using the OR connector, and the exit command also exits regardless of the AND connector.

- For the AND connector, if the first command the second command are false, a semicolon followed by a command will not execute.

- Some chains of commands produce incorrect input specifically involving the AND and OR connectors.
