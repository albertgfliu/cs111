//main.c
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

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
	int arg_cnt;

	//insert check for if first argument is an option. otherwise there's a problem

	curr_optind = optind;
	curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
	next_optind = optind;
	if(curr_opt == -1){
		fprintf(stderr, "error: no options found\n");
	}
	else {
		/*
		insert check for if argv[1] is an option. otherwise there's a problem.
		*/
		do {

		printf("curr_optind = %d | curr_opt = %c | next_optind = %d\n", curr_optind, curr_opt, next_optind);
		printf("argv[%d] = %s\n", next_optind, argv[next_optind]);

		switch(curr_opt){
			case 'r':
				//if(next_optind != curr_optind + 2)
				//	fprintf(stderr, "error: rdonly can only accept one argument\n"); //print to stderror?
				//else
					printf("rdonly with arg %s\n", optarg);
				if(verbose_flag){
					printf("--rdonly %s\n", optarg);
				}
				break;
			case 'w':
				//if(next_optind != curr_optind + 2)
				//	fprintf(stderr, "error: wronly can only accept one argument\n"); //print to stderror?
				//else
					printf("wronly with args %s\n", optarg);
				if(verbose_flag){
					printf("--wronly %s\n", optarg);
				}
				break;
			case 'p':
				//if(next_optind != curr_optind + 1)
				//	fprintf(stderr, "error: pipe can not have any arguments\n");	
				printf("pipe\n");
				printf("pipe with arg = %s\n", optarg);	
				if(verbose_flag){
					printf("--pipe\n");
				}
				break;
			case 'c': //special case, will take more work
				//if(next_optind < curr_optind + 5)
				//	fprintf(stderr, "error: command needs more arguments\n");
				printf("command with args %s\n", optarg);
				if(verbose_flag){
					printf("--command %s\n", optarg);
				}
				break;
		}
		
		curr_optind = optind;
		curr_opt = getopt_long(argc, argv, "", long_opts, &long_opts_ind);
		next_optind = optind;

		} while(curr_opt != -1);
	}

  return EXIT_SUCCESS;
}
