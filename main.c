#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "build_in.h"
#include "functions.h"
#include "shell.h"


int main(int argc, char **argv)
{
	printf("########################\n# Welcome in PonyShell #\n########################\n");
	psh_loop();

	return 0;//EXIT_SUCCESS;
}
