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

/*! \brief Funkcja uaktualniająca czas modyfikacji.
 *
 * Funkcja zmienająca w podanym pliku (*name) czas ostatniej modyfikacji.
 *
 * \param[in] *name Nazwa pliku w, którym ma zostać zmieniony czas modyfikacji.
 */
void change_mtime(char *name)
{
  struct stat foo;
  time_t mtime;
  struct utimbuf new_times;

  stat(name, &foo);
  mtime = foo.st_mtime;

  new_times.actime = foo.st_atime;
  new_times.modtime = time(NULL);
  utime(name, &new_times);
}

int main(int argc, char **argv)
{
	FILE *file;
	int c,j;
	file = fopen(argv[1], "w");
	fclose(file);

  change_mtime(argv[1]);
  return 0;
}
