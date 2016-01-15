# UCLA CS 111 Winter 2016 Lab 1 - Simpleton Shell

Things of note:
argc stands for argument count, and counts the number of arguments we have to our main function. Arguments are denoted as strings separated by a space.
When our program is run, e.g.:
    ./simpsh --rdonly a --wronly b --pipe --rdonly c
There are 8 arguments, which are stored in the string array argv as follows:
    argv[0] = ./simpsh
    argv[1] = --rdonly
    argv[2] = a
    argv[3] = --wronly 
    argv[4] = b
    argv[5] = --pipe
    argv[6] = --rdonly
    argv[7] = c

The “command” implementation assumes that the command is valid in the form of:
—command  stdin stdout stderr cmd arg arg…

It does not check if the file descriptor numbers are valid or are actually numbers.

“For the purpose of this lab, you do not need to care if a command exists or whether the arguments to the command are valid. execvp just takes whatever there and executes (which may fail or succeed).” According to our TA, Tuan Le