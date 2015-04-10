%{
#ifndef YYSTYPE
#define YYSTYPE char*
#endif
#define YYDEBUG 1
#include "global.h"

extern int isCommandValue;

  void yyerror(const char *str)
{
        //fprintf(stderr,"error: %s\n",  str);
}

int yywrap()
{
        return 1;
}

%}

%token PIPE LEFT_OPEN RIGHT_OPEN ERROR_CMD COMMAND VALUE OPTION EOL 

%%

start: command EOL  { return 0; };

command:  { insertCmd.name = "empty"; cmdTab[numTabCmds++] = insertCmd;}
	  |	COMMAND  axis { printf("Command axis %s\n", $1); 
	  					insertCmd.name = $1; 
	  					insertCmd.args[0] = insertCmd.name;
	  					cmdTab[numTabCmds++] = insertCmd;
	  				  }
      | COMMAND { printf("Command %s\n", $1); 
      			  insertCmd.name = $1; 
      			  insertCmd.args[0] = insertCmd.name;
      			  cmdTab[numTabCmds++] = insertCmd;
      			  }
      | VALUE axis  { insertCmd.name = $1; 
      					insertCmd.args[0] = insertCmd.name;
	  					cmdTab[numTabCmds++] = insertCmd; }
      | VALUE       { insertCmd.name = $1; 
      					insertCmd.args[0] = insertCmd.name;
	  					cmdTab[numTabCmds++] = insertCmd; }
      | OPTION axis { insertCmd.name = $1; return 1; }
      | OPTION      { insertCmd.name = $1; return 1; };

axis: inter | axis inter ;

inter: VALUE  { isCommandValue = true;
                insertCmd.args[++insertCmd.numArgs] = $1;
                printf("Inter value %s\n", insertCmd.args[insertCmd.numArgs]);
              }
       | OPTION { insertCmd.args[++insertCmd.numArgs] = $1;
       			  printf("Inter option %s\n", insertCmd.args[insertCmd.numArgs]);
       			}
       | COMMAND { printf("extra unhandled command: %s\n", $1); };
%%
