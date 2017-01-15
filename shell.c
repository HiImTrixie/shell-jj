#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int psh_cd(char **args);
int psh_help(char **args);
int psh_exit(char **args);
int psh_man(char **args);
int psh_cat(char **args);
int psh_touch(char **args);
int psh_rm(char **args);
int psh_cp(char **args);

char *builtin_str[] = 
{
	"cd",
	"help",
	"exit",
	"man",
	"cat",
	"touch",
	"rm",
	"cp"
};
int (*builtin_func[]) (char **) =
{
	&psh_cd,
	&psh_help,
	&psh_exit,
	&psh_man,
	&psh_cat,
	&psh_touch,
	&psh_rm,
	&psh_cp
};
int psh_num_builtins()
{
	return sizeof(builtin_str) / sizeof(char *);
}
int psh_cp(char **args)
{
        FILE *fp1= NULL, *fp2= NULL;
        if(args[1] && args[2])
        {
                fp1 = fopen(args[1], "r");
                fp2 = fopen(args[2], "w");
                char buff[1024];
                for(int i=0; fscanf(fp1, "%s", &buff) != -1; i++)
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

int psh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if(pid == 0)
	{
		if(execvp(args[0], args) == -1)
		{
			perror("PonyShell");
		}
		exit(EXIT_FAILURE);
		}
		else if(pid < 0)
		{
			perror("PonyShell");
		}
		else
		{
			do
			{
				wpid = waitpid(pid, &status, WUNTRACED);
			}
			while(!WIFEXITED(status) && !WIFSIGNALED(status));
		}

	return 1;
	
}

int psh_execute(char **args)
{
	int i;
	
	if(args[0] == NULL)
	{
		return 1;
	}
	for(i = 0; i < psh_num_builtins(); i++)
	{
		if(strcmp(args[0], builtin_str[i]) == 0)
		{
			return(*builtin_func[i])(args);
		}
	}
	return psh_launch(args);
}

#define PSH_TOK_BUFSIZE 64
#define PSH_TOK_DELIM " \t\r\n\a"

char **psh_split_line(char *line)
{
	int bufsize = PSH_TOK_BUFSIZE, position=0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token, **tokens_backup;
	if(!tokens)
	{
		fprintf(stderr, "PonyShell: Allocation Error\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, PSH_TOK_DELIM);
	while(token != NULL)
	{
		tokens[position] = token;
		position++;
		if(position >= bufsize)
		{
			bufsize += PSH_TOK_BUFSIZE;
			tokens_backup = tokens;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if(!tokens)
			{
				free(tokens_backup);
				fprintf(stderr, "PonyShell: Allocation Error\n");
				exit(EXIT_FAILURE);
			}
		}
	token = strtok(NULL, PSH_TOK_DELIM);
	}
	tokens[position] = NULL;
	return tokens;
}

char *psh_read_line(void)
{
	char *line = NULL;
	ssize_t bufsize = 0;
	getline(&line, &bufsize, stdin);
	return line;
}

void psh_loop(void)
{
	char *line;
	char **args;
	int status;
	char cwd[1024];
	do
	{
		printf("%s$ ", getcwd(cwd, sizeof(cwd)));
		line = psh_read_line();
		args = psh_split_line(line);
		status = psh_execute(args);

		free(line);
		free(args);
	}
	while (status);
}

int main(int argc, char **argv)
{
	printf("########################\n# Welcome in PonyShell #\n########################\n");
	psh_loop();

	return 0;//EXIT_SUCCESS;
}
