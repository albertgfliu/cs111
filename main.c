// main.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

// defines
#define TRUE 1
#define FALSE 0

// global variables
static int verbose_flag;
// logical to real file descriptors
static int fd[1000];

// helper functions
int isOption(char *cstring){
	if((cstring[0] != '-') || (cstring[1] != '-'))
		return FALSE;
	else
		return TRUE;
}

// MUST PRINT ERROR MESSAGES FOR INVALID ARGUMENTS

// main function
int main(int argc, char **argv){

	static struct option long_opts[] = 
	{
		/* options that set a flag */
		{"verbose", no_argument, &verbose_flag, 1},
 
		/* options that don't set a flag */
		{"rdonly",	required_argument,	0, 	'r'},
		{"wronly",	required_argument,	0,	'w'},
		{"command",	required_argument,	0,	'c'},
		{"pipe",	no_argument,		0, 	'p'},
		{0, 		0, 			0, 	0}
	};
	
	int long_opts_ind;
	int curr_opt;
	int curr_optind;
	int next_optind;

	int fd_ind = 0;

	curr_optind = optind;
	curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
	next_optind = optind;
	if(curr_opt == -1){
		fprintf(stderr, "Error: no options found\n");
	}
	else {
		if(!isOption(argv[curr_optind])){
			fprintf(stderr, "Error: argument found before options and was ignored\n");
		}
		do {
			//debug message
			//printf("curr_optind = %d | curr_opt = %c | next_optind = %d\n", curr_optind, curr_opt, next_optind);
			//printf("argv[%d] = %s\n", next_optind, argv[next_optind]);
			//printf("optopt = %d\n", optopt);
	
			switch(curr_opt){
				case 'r':{
					if((next_optind != argc) && !isOption(argv[next_optind])){
						fprintf(stderr, "Error: --rdonly can only accept one argument, further arguments to rdonly were ignored\n");
					}
					int temp_fd = open(optarg, O_RDONLY, 644);
					if (temp_fd < 0){
						fprintf(stderr, "Error: could not open file \"%s\" for read\n", optarg);
                        exit(EXIT_FAILURE);
					}
					else{
						fd[fd_ind++] = temp_fd;
					}
					if(verbose_flag){
						printf("--rdonly %s\n", optarg);
					}
					break;
				}
				case 'w':{
					if((next_optind != argc) && !isOption(argv[next_optind])){
						fprintf(stderr, "Error: wronly can only accept one argument, further arguments to wronly were ignored\n");
					}
					int temp_fd = open(optarg, O_WRONLY, 644);
					if (temp_fd < 0){
						fprintf(stderr, "Error: could not open file \"%s\" for write\n", optarg);
                        exit(EXIT_FAILURE);
					}
					else{
						fd[fd_ind++] = temp_fd;
					}
					if(verbose_flag){
						printf("--wronly %s\n", optarg);
					}
					break;
				}
				case 'c':{
                    pid_t pid, wpid;
                    pid = fork();
                    char **arg;
                    if (pid == 0) {
                        int arg_fd[3];
                        int arg_ind = 0;
                        
                        /* handling file descriptors */
                        for (int i = 0; i < 3; i++) {
                            arg_fd[i] = atoi(argv[next_optind + i]);
                        }
                        
                        /* handling arguments */
                        int next_notFdOptind = next_optind + 3;
                        for (; ((next_notFdOptind + arg_ind) != argc ) && !isOption(argv[next_notFdOptind + arg_ind]); arg_ind++) {
                            arg[arg_ind] = argv[next_notFdOptind + arg_ind];
                        }
                        arg[arg_ind] = NULL;
                        
                        /* prepare standard streams */
                        dup2(arg_fd[0], STDIN_FILENO);
                        dup2(arg_fd[1], STDOUT_FILENO);
                        dup2(arg_fd[2], STDERR_FILENO);
                        
                        if(verbose_flag){
                            printf("--commmand");
                            for (int i = 0; i < 3; i++) {
                                printf(" %c", arg_fd[i]);
                            }
                            for (int j = 0; j < arg_ind; j++) {
                                printf(" %s", arg[j]);
                            }
                        }

                        if (execvp(arg[0], arg) == -1) {
                            fprintf(stderr, "Error: cannot execute command \"%s\"\n", argv[0]);
                            exit(EXIT_FAILURE);
                        }
                    }
                    else if (pid < 0) {
                        fprintf(stderr, "Error: cannot execute command \"%s\"\n", argv[0]);
                    }
                    else {
                        int status, exstat;
                        waitpid(pid, &status, 0);
                        
                        /* to get the lower 8-bit of the exit status */
                        exstat = WEXITSTATUS(status);
                    }
					break;
				}
				case '?':{
					fprintf(stderr, "Error: option not recognized or no option argument found\n");
					break;
				}
                default:
                    break;
			}

			//move to next option
			while((optind != argc) && !isOption(argv[optind]))
				optind++;
			curr_optind = optind;
			curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
			next_optind = optind;
		} while(curr_opt != -1);
	}

	for(int i = 0; i < fd_ind; i++){
		if(close(fd[i]) != 0)
			fprintf(stderr, "Error: could not close file at logical index %d", i);
	}

  return EXIT_SUCCESS;
}
