#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "build_in.h"
#include "functions.h"
#include "parse.h"
#include "globals.h"
char *built_in_str[] =
{
	"cd",
	"help",
	"exit",
	"man",
	"cat",
	"touch",
	"rm",
	"cp",
	"history"
};
void psh_history()
{
	int row = 1;
	char temp[MAXTOKENLEN + 1];
	FILE *history = fopen(".history", "r");
	while(fgets(temp, MAXTOKENLEN + 1, history) != NULL){
		fprintf(stdout, "%d %s", row, temp);
		row++;
	}
	fclose(history);

}
void psh_cp()
{
        FILE *fp1= NULL, *fp2= NULL;
        if(arg[1][0] && arg[1][1])
        {
                fp1 = fopen(arg[1][0], "r");
                fp2 = fopen(arg[1][1], "w");
                char symbol;
                for(int i=0; ( symbol = fgetc(fp1)) != -1; i++)
                  fputc(symbol, fp2);
                fclose(fp1);
                fclose(fp2);
        }
        else
        {
                fprintf(stderr, "Not enough or too many arguments\n");
        }
}
void psh_rm()
{
	if(arg[1][0] == NULL)
	{
		fprintf(stderr, "No arguments were given.\n");
		return 1;
	}
	else
	{
		remove(arg[1][1]);
	}
}
void psh_touch()
{
	FILE *fp;
	int c,j;
	if(arg[1][0] == NULL)
	{
		fprintf(stderr, "No arguments were given.\n");
		return 1;
	}
	else if(arg[1][0] && arg[1][1] == NULL)
	{
		fp = fopen(arg[1], "w");
		fclose(fp);
	}
}
void psh_cat()
{
	FILE *fp;
	int c;
	if(arg[1][0] == NULL)
	{
		fprintf(stderr, "No file were given\n");
		return 1;
	}
	else
	{
		fp = fopen(arg[1][0], "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
}
void psh_man()
{
	FILE *fp;
	int c;
	if(arg[1][0] == NULL)
	{
		printf("You have to type what function you want to check.\n");
		printf("Example: man ls\n");
	}
	else if(strcmp(arg[1][0], "cd") == 0)
	{
		fp = fopen("man/cd.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(arg[1][0], "exit") == 0)
	{
		fp = fopen("man/exit.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(arg[1][0], "pwd") == 0)
	{
		fp = fopen("man/pwd.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(arg[1][0], "ls") == 0)
	{
		fp = fopen("man/ls.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(arg[1][0], "man") == 0)
	{
		fp = fopen("man/man.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
	else if(strcmp(arg[1][0], "cat") == 0)
	{
		fp = fopen("man/cat.txt", "r");
		if(fp)
		{
			while((c = getc(fp)) != EOF)
				putchar(c);
			fclose(fp);
		}
	}
  putchar('\n');
}
void psh_cd()
{
	if(arg[1][0] != 0)
	{
		if(!chdir(arg[1]))
			strcpy(pwd, arg[1]);
		else
		{
			if(errno = ENOENT)
			{
				fprintf(stdout, "PSH: cd: %s: No such file or directory\n", arg[1]);
			}
			else if(errno == ENOTDIR)
			{
				fprintf(stdout, "PSH: cd: %s: Not a directory\n", arg[1]);
				errno = 0;
			}
		}
	}
}

void psh_help()
{
	int i;
	printf("PonyShell written by Mateusz Gorczycki, Grzegorz Jaworski, Adrian Rupala.\n");
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are build in:\n");

	for(i = 0; i < psh_num_builtins(); i++)
	{
		printf(" %s\n", built_in_str[i]);
	}
}
void psh_exit()
{
	exit(atoi(arg[1]));
}
