#include <string.h>
#include "build_in.h"
#include "functions.h"

#define num_buildins 8

int isbuildin(char *s)
{
	BuildInType command = NO;

	if(!strcmp(s, "cd"))
		command = CD;
	else if (!strcmp(s, "help"))
		command = HELP;
	else if (!strcmp(s, "exit"))
		command = EXIT;
	else if (!strcmp(s, "man"))
		command = MAN;
  else if (!strcmp(s, "cat"))
  	command = CAT;
	else if (!strcmp(s, "touch"))
  	command = TOUCH;
  else if (!strcmp(s, "rm"))
  	command = RM;
  else if (!strcmp(s, "cp"))
    command = CP;
	else if(!strcmp(s, "history"))
		command =  HISTORY;

  return command;
}

void runbuildin(BuildInType command)
{
	switch(command)
	{
		case CD:
			psh_cd();
			break;
		case HELP:
			psh_help();
			break;
		case EXIT:
			psh_exit();
			break;
		case MAN:
      psh_man();
    case CAT:
      psh_cat();
      break;
    case TOUCH:
      psh_touch();
      break;
    case RM:
      psh_rm();
		  break;
    case CP:
      psh_cp();
      break;
    case HISTORY:
      psh_history();
      break;
		case NO:/* nothing */
		default:break;
	}
}

int psh_num_builtins()
{
	return num_buildins;
}
