#include "global.h"

void main() {
	cd = 0;
    
    init();
	while(1){
		prompt();
		switch(getCommand()){
			case BYE:
				exit(0);
			case ERROR:
				handle_errors(); break;
			case OK:
				processCommand(); break;
		}
	}
}

void init(){
	get_curr_dir();
	home = getenv("HOME");
	// init all variables. 
	// define (allocate storage) for some var/tables
	// init all tables (e.g., alias table)
	// get PATH environment variable (use getenv())
	// get HOME env variable (also use getenv())
	// disable anything that can kill your shell. 
	// (the shell should never die; only can be exit)
	// do anything you feel should be done as init
}

void prompt(){
	get_curr_dir();
	printf("%s\nasShell:%s%s%s>%s", KCYN, KGRY, cwd, KCYN, KNRM);
}

int getCommand(){
	//initialize parse and int. set what variable builtin is
	if (yyparse()) 
		return understand_errors();
	else
		return OK;
}

void processCommand(){
	if (builtin) 
		do_it();		// run built-in commands – no fork
						// no exec; only your code + Unix
						//system calls. 
	else 
		execute_it();	// execute general commands
						//using fork and exec
}

void do_it() {
	switch (builtin) {
	  /*case ALIAS:	// e.g., alias(); alias(name, word);
	  case CDHome: 	// e.g., gohome();
	  case CDPath:	// e.g., chdir(path);	
	  case UNALIAS:
	  case SETENV:
	  case PRINTENV:*/
	  //...
	}
}

void execute_it(){
	//CHECK SLIDES FOR MORE CODE EXAMPLES ON THIS METHOD/////////////////////////////

	// Handle  command execution, pipelining, i/o redirection, and background processing. 
	// Utilize a command table whose components are plugged in during parsing by yacc. 

	/* 
	 * Check Command Accessability and Executability
	*/

	
	/*
	 * Check io file existence in case of io-redirection.
	*/
	
	//Build up the pipeline (create and set up pipe end points (using pipe, dup) 
	//Process background
}


int understand_errors(){
	printf("understand_errors()\n");
	return ERROR;
}

void handle_errors(){
	printf("handle_errors()\n");
	// Find out if error occurs in middle of command
	// That is, the command still has a “tail”
	// In this case you have to recover by “eating”
	// the rest of the command.
	// To do this: use yylex() directly.
}






char* get_curr_dir() {
	if (getcwd(cwd, sizeof(cwd)) == NULL){
		char *cwd = "";
		perror("no current working directory");
	} else {
		return cwd;
	}
	return cwd;
}

void changeDirectory(char* word) {
	if(strcmp(word, "home") == 0){
		cd = chdir(home);
	} else {
		cd = chdir(word);
	}
	
	if(cd == -1){
		fprintf(stdout, "directory %s/%s not found\n", get_curr_dir(), word);
	}else{
		//execlp("ls", "ls", "-l",(char *) NULL );
		//printf("chdir(%s) succeeded", word);
	}
}