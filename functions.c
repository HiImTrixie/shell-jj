#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "build_in.h"
#include "functions.h"

int psh_cp(char **args)
{
        FILE *fp1= NULL, *fp2= NULL;
        if(args[1] && args[2])
        {
                fp1 = fopen(args[1], "r");
                fp2 = fopen(args[2], "w");
                char buff[1024];
                for(int i=0; fscanf(fp1, "%s", buff) != -1; i++)
                  fprintf(fp2, "%s", buff);
                fclose(fp1);
                fclose(fp2);
        }
        else
        {
                fprintf(stderr, "Not enough or too many arguments\n");
        }
	return 1;
}
int psh_rm(char **args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "No arguments were given.\n");
		return 1;
	}
	else
	{
		remove(args[1]);
	}
	return 1;
}
int psh_touch(char **args)
{
	FILE *fp;
	int c,j;
	if(args[1] == NULL)
	{
		fprintf(stderr, "No arguments were given.\n");
		return 1;
	}
	else if(args[1] && args[2] == NULL)
	{
		fp = fopen(args[1], "w");
		fclose(fp);
	}
	else
	{
		for(int i = 1; args[i] != NULL; i++)
		{
			fp = fopen(args[i], "w");
			fclose(fp);
		}
	}
	return 1;
}
int psh_cat(char **args)
{
	FILE *fp;
	int c;
	if(args[1] == NULL)
	{
		fprintf(stderr, "No file were given\n");
		return 1;
	}
	else
	{
		fp = fopen(args[1], "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	return 1;
}
int psh_man(char **args)
{
	FILE *fp;
	int c;
	if(args[1] == NULL)
	{
		printf("You have to type what function you want to check.\n");
		printf("Example: man ls\n");
	}
	else if(strcmp(args[1], "cd") == 0)
	{
		fp = fopen("man/cd.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(args[1], "exit") == 0)
	{
		fp = fopen("man/exit.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(args[1], "pwd") == 0)
	{
		fp = fopen("man/pwd.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(args[1], "ls") == 0)
	{
		fp = fopen("man/ls.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(args[1], "man") == 0)
	{
		fp = fopen("man/man.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(args[1], "cat") == 0)
	{
		fp = fopen("man/cat.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	return 1;
}
int psh_cd(char **args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "PonyShell: Expected argument to \"cd\"\n");
	}
	else
	{
		if(chdir(args[1]) != 0)
		{
			perror("PonyShell");
		}
	}
	return 1;
}

int psh_help(char **args)
{
	int i;
	printf("PonyShell written by Mateusz Gorczycki, Grzegorz Jaworski, Adrian Rupala.\nBased on Stephen Brennan's Shell.\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are build in:\n");

	for(i = 0; i < psh_num_builtins(); i++)
	{
		printf(" %s\n", builtin_str[i]);
	}
}

int psh_exit(char **args)
{
	return 0;
}
