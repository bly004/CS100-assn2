#rshell
This program is a Shell terminal written in C++. It executes commands with the syscalls fork, execvp, and waitpid. Such commands include `ls`, `echo`, `exit`, etc.

##Installation
To install and run the rshell program:

1. Open a terminal and clone the repository

  `git clone https://github.com/bly004/rshell.git`
2. Change directory into the project

  `cd rshell`
3. Switch branches

  `git checkout hw2`
4. Create exeutables

  `make`
5. Execute rshell

  `bin/rshell`
  
##Program Features
* rshell supports all commands in /bin
* rshell also supports connectors (`;`, `&&`, `||`) and comments (`#`)
  * the `;` connector: the command followed by `;` is always executed
  * the `&&` connector: the command followed by `&&` is executed only if the first one succeeds
  * the `||` connector: the command followed by `||` is executed only if the first one fails
  * the `#` symbol: anything after this symbol is considered a comment and does not affect the command
* exiting the program requires the typing of `exit`

##Bugs and Limitations
* Sometimes spaces can mess up parsing and result in a failed commmand
