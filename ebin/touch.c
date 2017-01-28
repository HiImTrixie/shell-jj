/*! \file touch.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.1
 *  \brief Tworzenie nowego pliku
 *  \details Program wyświetlajacy zawartość wskazanych plików
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>

int main(int argc, char **argv)
{
	FILE *file;
	int c,j;
	if(argv[1] == NULL)
	{
		fprintf(stderr, "No arguments were given.\n");
		return 1;
	}
	else if(argv[1] && argv[2] == NULL)
	{
		file = fopen(argv[1], "w");
		fclose(file);
	}
	else
	{
		for(int i = 1; argv[i] != NULL; i++)
		{
			file = fopen(argv[i], "w");
			fclose(file);
		}
	}
	return 1;
}
