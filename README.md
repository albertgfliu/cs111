# UCLA CS 111 Winter 2016 Lab 1c - Simpleton Shell

NOTE: Concerning the make check scripts, there are differences between testing on the SEASnet Linux Servers and testing on our local machines. We corrected our implementation to be compatible with the Linux Servers so they may not run correctly on our local machines.

There are several things worth noting in our implementation of the simpsh, 1c:

1. We made an assumption that the amount of file descriptors opened would not exceed 1000.

2. We assume that the options of simpsh referring to the logical file descriptors 
do not know if these fds are operating or not prior to execution. Thus, we still 
maintained a logical fd number fd[] for each file. If the "open" fails, 
the logical fd can be mapped to a dummy value to signify invalid fd. 

3. The simpsh “command” option does not check if the file descriptor numbers are valid.

4. For the purpose of this lab 1, we assume the user is advised of the correct format of the arguments following “command”. execvp() just takes whatever there and executes 
(which may fail or succeed).

5. We assume that without the “wait” option, it is possible that none of the 
child processes of the subshells will finish before simpsh finishes executing 
all of its options. We implemented the “command” option by obtaining the 
status of child process with WNOHANG without "actually waiting" for any process to terminate.

6. In the Makefile, we use the -std=gnu11 to compile our source file

7. We assumed that the usage of threads are not allowed in the simpsh program, to make the signal handling easier in this case

8. For the implementation of the --ignore option, we increment the instruction pointer %rip to avoid the infinite loop as a result of SIGSEGV

9. --wait shoudl only wait on the previous commands

10. We assume the arguments to command will not exceed 100

11. The number of pipes opened will not exceed 500.
