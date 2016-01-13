//main.c
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

<<<<<<< HEAD
//global variables
int verbose_flag;

int main(int argc, char **argv){

	int curr_opt;
	int curr_optind;
	int next_opt;
	int next_optind;
	int argv_index;

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
	
	curr_optind = 1;
	next_opt = getopt_long(argc, argv, "", long_opts, NULL);
	next_optind = optind;
	while(next_opt != -1){
		curr_opt = next_opt;

		printf("curr_optind = %d, next_optind = %d\n", curr_optind, next_optind);
		switch(curr_opt){
			case 'r': //consume one file number
				if(next_optind != curr_optind + 2)
					printf("error: rdonly can only accept one argument\n"); //print to stderror?
				else
					printf("rdonly with arg %s\n", optarg);
				break;
			case 'w': //consume one file number
				if(next_optind != curr_optind + 2)
					printf("error: wronly can only accept one argument\n"); //print to stderror?
				else
					printf("rdonly with args %s\n", optarg);
				break;
				printf("wronly with arg %s\n", optarg);
				break;
			case 'p': //consumes two file numbers

				if(next_optind != curr_optind + 1)
					printf("error: pipe can not have any arguments");			
				printf("pipe\n");
				printf("pipe with arg = %s\n", optarg);	
				break;
			case 'c': //special case, will take more work
				//parse multiple arguments
				printf("command with args %s\n", optarg);
				break;
		}
		
		curr_optind = next_optind;
		next_opt = getopt_long(argc, argv, "", long_opts, NULL);
		next_optind = optind;
	}
  return EXIT_SUCCESS;
