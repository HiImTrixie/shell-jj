/*! \file touch.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.2
 *  \brief Zmiana czasu modyfikacji pliku
 *  \details Program zmieniający czas ostatniej modyfikacji podanych plików.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <sys/stat.h>
#include <time.h>
#include <utime.h>



int main(int argc, char **argv)
{
	FILE *file;
	int c,j;
	file = fopen(argv[1], "w");
	fclose(file);

  struct stat foo;
  time_t mtime;
  struct utimbuf new_times;

  stat(argv[1], &foo);
  mtime = foo.st_mtime;

  new_times.actime = foo.st_atime;
  new_times.modtime = time(NULL);
  utime(argv[1], &new_times);

  return 0;
}
