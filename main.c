//main.c
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include <unistd.h>

//defines
#define TRUE 1
#define FALSE 0
#define cmd_size 100

//global variables
static int verbose_flag;
static int wait_flag;
static int fd[1000];
static int pipe_fd[2];
static int cmd_fd[3];
char *cmd[cmd_size];
static int return_val;
//char *cmd[20];

//helper function
int isAnOption(char *cstring){
	if((cstring[0] != '-') || (cstring[1] != '-'))
		return FALSE;
	else
		return TRUE;
}

void flushCmd(){
	for(int i = 0; i < cmd_size; i++)
		cmd[i] = NULL;
}

//MUST PRINT ERROR MESSAGES FOR INVALID ARGUMENTS

//main function
int main(int argc, char **argv){

	static struct option long_opts[] = 
	{
		/*options that set a flag*/
		{"verbose", no_argument, &verbose_flag, 1},
		{"wait", no_argument, &wait_flag, 1},

		/*options that don't set a flag*/
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
	int cmd_ind = 0;

	verbose_flag = 0;
	wait_flag = 0;

	return_val = 0;

	pid_t pid;
	pid_t c_pid;
	
	curr_optind = optind;
	curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
	next_optind = optind;
	if(curr_opt == -1){
		fprintf(stderr, "error: no options found\n");
	}
	else {
		if(!isAnOption(argv[curr_optind])){
			fprintf(stderr, "error: argument found before options and was ignored\n");
		}
		do {
			//debug message
			//printf("curr_optind = %d | curr_opt = %c | next_optind = %d\n", curr_optind, curr_opt, next_optind);
			//printf("argv[%d] = %s\n", next_optind, argv[next_optind]);
			//printf("optopt = %d\n", optopt);
	
			switch(curr_opt){
				case 'r':{
					if((next_optind != argc) && !isAnOption(argv[next_optind])){
						fprintf(stderr, "error: rdonly can only accept one argument, further arguments to rdonly were ignored\n");
					}
					if(verbose_flag){
						printf("--rdonly %s\n", optarg);
					}
					int temp_fd = open(optarg, O_RDONLY, 644);
					if (temp_fd == -1){
						fprintf(stderr, "error: could not open file \"%s\" for read\n", optarg);
					}
					fd[fd_ind++] = temp_fd;
					
					break;
				}
				case 'w':{
					if((next_optind != argc) && !isAnOption(argv[next_optind])){
						fprintf(stderr, "error: wronly can only accept one argument, further arguments to wronly were ignored\n");
					}
					if(verbose_flag){
						printf("--wronly %s\n", optarg);
					}
					int temp_fd = open(optarg, O_WRONLY, 644);
					if (temp_fd == -1){
						fprintf(stderr, "error: could not open file \"%s\" for write\n", optarg);
					}
					fd[fd_ind++] = temp_fd;
					
					break;
				}
				case 'p':{
					if((next_optind != argc) && !isAnOption(argv[next_optind])){
						fprintf(stderr, "error: pipe can not accept any arguments, all arguments to pipe were ignored\n");
					}
					if(verbose_flag){
						printf("--pipe\n");
					}
					if(pipe(pipe_fd) == -1){
						fprintf(stderr, "error: failure to create a pipe\n");
					}
					fd[fd_ind++] = pipe_fd[0];
					fd[fd_ind++] = pipe_fd[1];

					break;
				}
				case 'c':{
					while((optind != argc) && !isAnOption(argv[optind])){
						optind++;
					}
					if(optind < (curr_optind + 5))
						fprintf(stderr, "error: missing arguments to --command, your command will not be run\n");
					else{
						
						
						cmd_fd[0] = atoi(optarg);
						cmd_fd[1] = atoi(argv[next_optind++]);
						cmd_fd[2] = atoi(argv[next_optind++]);

						cmd_ind = 0;
						//for(int i = 0; i < 3; i++)
						//	printf("cmd_fd[%d] = %d\n", i, cmd_fd[i]);
						
						flushCmd();

						while((next_optind != argc) && !isAnOption(argv[next_optind])){
							char *char_ptr = malloc(sizeof(argv[next_optind]));
							//printf("%d ", (int)sizeof(argv[next_optind]));
							cmd[cmd_ind] = char_ptr;
							strcpy(cmd[cmd_ind], argv[next_optind]);
							cmd_ind++;
							next_optind++;
						}
						if(verbose_flag){
							printf("--command");
							for(int i = 0; i < 3; i++){
								printf(" %d", cmd_fd[i]);
							}
							for(int i = 0; i < cmd_size; i++){
								if(cmd[i] != NULL){
									printf(" %s", cmd[i]);
								}
							}
							printf("\n");
						}
						
						c_pid = fork();
						if(c_pid == 0){	
							
							dup2(fd[cmd_fd[0]], STDIN_FILENO);
							dup2(fd[cmd_fd[1]], STDOUT_FILENO);
							dup2(fd[cmd_fd[2]], STDERR_FILENO);
							if(execvp(cmd[0], cmd) == -1){
								fprintf(stderr, "error: command failed");
							}
						}
						else if(c_pid > 0){
							int status;
							waitpid(c_pid, &status, 0);
							int exit_status = WEXITSTATUS(status);
							if(wait_flag){
								printf("%d", exit_status);
								for(int i = 0; i < cmd_size; i++){
									if(cmd[i] != NULL){
										printf(" %s", cmd[i]);
									}
								}
								printf("\n");
							}
							if(exit_status > return_val)
								return_val = exit_status;
						}
						else{ //couldn't create child process
							fprintf(stderr, "error: could not create child process\n");
						}
						
						
						for(int i = 0; i < cmd_size; i++)
							free(cmd[i]);
						
					}
					
					break;
				}
				case '?':{
					fprintf(stderr, "error: option not recognized or no option argument found\n");
					break;
				}
			}

			//move to next option
			while((optind != argc) && !isAnOption(argv[optind]))
				optind++;
			curr_optind = optind;
			curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
			next_optind = optind;
		} while(curr_opt != -1);
	}

	for(int i = 0; i < fd_ind; i++){
		if(close(fd[i]) != 0){
			fprintf(stderr, "error: could not close file at logical index %d\n", i);
		}
	}

  return return_val;
}
