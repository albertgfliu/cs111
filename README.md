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
