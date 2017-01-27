/*! \file cat.c
 *  \author Grzegorz Jaworski
 *  \date 27 Styczeń 2017
 *  \version   v0.1
 *  \brief Wyświetlanie zawartości pliku
 *  \details Program wyświetlajacy zawartość wskazanych plików
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */

#include <stdio.h>


void cat(char *name)
{
  FILE *file;
  int c;
  file = fopen(name, "r");
  if(file)
  {
    while((c = getc(file)) != EOF)
      putchar(c);
    fclose(file);
  }
}


int main(int argc, char **argv)
{
  if(argv[1] == NULL)
  {
    fprintf(stderr, "No file were given\n");
    return 1;
  }
  else
  {
    cat(argv[1]);
  }
  return 0;
}
