//main.c
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

//defines
#define TRUE 1
#define FALSE 0

//global variables
int verbose_flag;

//helper function
int isAnOption(char *cstring){
	if((cstring[0] != '-') || (cstring[1] != '-'))
		return FALSE;
	else
		return TRUE;
}

//MUST PRINT ERROR MESSAGES FOR INVALID ARGUMENTS

//main function
int main(int argc, char **argv){

	static struct option long_opts[] = 
	{
		/*options that set a flag*/
		{"verbose", no_argument, &verbose_flag, 1},

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

	//insert check for if first argument is an option. otherwise there's a problem

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
			//printf("curr_optind = %d | curr_opt = %c | next_optind = %d\n", curr_optind, curr_opt, next_optind);
			//printf("argv[%d] = %s\n", next_optind, argv[next_optind]);
	
			switch(curr_opt){
				case 'r':
					if((next_optind != argc) && !isAnOption(argv[next_optind])){
						fprintf(stderr, "error: rdonly can only accept one argument, further arguments to wronly were ignored\n");
					}
					if(verbose_flag){
						printf("--rdonly %s\n", optarg);
					}
					break;
				case 'w':
					if((next_optind != argc) && !isAnOption(argv[next_optind])){
						fprintf(stderr, "error: wronly can only accept one argument, further arguments to wronly were ignored\n");
					}
					if(verbose_flag){
						printf("--wronly %s\n", optarg);
					}
					break;
				case 'p':
					if((next_optind != argc) && !isAnOption(argv[next_optind])){
						fprintf(stderr, "error: pipe can not accept any arguments, all arguments to pipe were ignored\n");
					}
					if(verbose_flag){
						printf("--pipe\n");
					}
					break;
				case 'c': //special case, will take more work
					printf("command with args %s\n", optarg);
					if(verbose_flag){
						printf("--command %s\n", optarg);
					}
					break;
			}

			//move to next option
			while((optind != argc) && !isAnOption(argv[optind]))
				optind++;
			curr_optind = optind;
			curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
			next_optind = optind;
		} while(curr_opt != -1);
	}

  return EXIT_SUCCESS;
}
