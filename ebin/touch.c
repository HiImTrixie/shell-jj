/*! \file touch.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.4
 *  \brief Zmiana czasu modyfikacji pliku
 *  \details Program zmieniający czas ostatniej modyfikacji podanych plików.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <utime.h>
#include <ctype.h> // library with isprint()
#include <getopt.h>

char version[64] = "v.0.4"; /*!< Aktualna wersja programu */

unsigned mdtime = 0; /*!< Zmień tylko czas modyfikacji */

unsigned actime = 0; /*!< Zmień tylko czas dostepu */

unsigned no_create = 0; /*!< Nie twórz nowego pliku */

// Content of help
static char const * const option_help[] =
{
"With no FILE read standard input.\n\n",
"  -a --atime  Change only access time.",
"  -c --no-create  Don't create new file.",
"  -m --mtime  Change only modification time.",
"  -v --version  Show version of program.",
"  -h --help  Output this help.",
0
};

/*! \brief Struktura zawierająca opcje programu.
 *
 *  Funcja zawierająca długie opcje pliku wywoływane przy pomocy podwójnego myślnika na przykład:--show-all .
 */
static struct option const long_options[] =
{
  {"no-create", 0, 0, 'c'},
  {"atime", 0, 0, 'a'},
  {"mtime", 0, 0, 'm'},
  {"version", 0, 0, 'v'},
  {"help", 0, 0, 'h'},
  {0, 0, 0, 0}
};

/*! \brief Funkcja wyświetla zawartość pomocy.
 *
 *  Funcja uruchamiana gdy użytkownik wpisze --help lub -h, wyświetla ona zawartość pomocy oraz przykładowe użycie.
 */
void usage()
{
  printf ("Usage: touch [OPTION]... [FILE]...\nUpdate times of access and modification all inserted files.\n\n");
  for (int i=0 ; option_help[i] != 0; i++)
    printf ("%s\n", option_help[i]);
}

/*! \brief Funkcja (wyświetla błąd)* oraz podpowiedz użycia pomocy.
 *
 *  Funcja wyświetla aktualny błąd jeżeli takowy wystąpił oraz podpowiedz użycia komendy wyświetlającej pomoc.
 */
static void try_help (char const *reason)
{
  if (reason)
    fprintf (stderr, "%s \n", reason);
  printf ("Try 'touch --help' for more information.\n");
  exit(EXIT_FAILURE);
}

/*! \brief Funkcja wyświetla aktualna wersje programu.
 *
 * Funkcja wyświetla wersje programu po podaniu jako argumentu -v oraz zamyka program.
 */
void pversion()
{
  printf ("Touch\nVersion: %s\n", version);
  exit(-1);
}

/*! \brief Funkcja uaktualniająca czas modyfikacji.
 *
 * Funkcja zmienająca w podanym pliku (*name) czas ostatniej modyfikacji.
 *
 * \param[in] *name Nazwa pliku w, którym ma zostać zmieniony czas modyfikacji.
 */
void change_time(char *name)
{
  struct stat foo;
  time_t mtime;
  struct utimbuf new_times;

  stat(name, &foo);
  mtime = foo.st_mtime;
  if ((mdtime && actime) || !mdtime && !actime){
    new_times.actime = time(NULL); // foo.st_atime
    new_times.modtime = time(NULL);
  }else if (mdtime){
    new_times.actime = foo.st_atime;
    new_times.modtime = time(NULL);
  }else if (actime){
    new_times.actime = time(NULL);
    new_times.modtime = foo.st_mtime;
  }
  utime(name, &new_times);
}

int main(int argc, char **argv)
{
  FILE *file;
  int c, index;

  while ((c = getopt_long (argc, argv,
          "acmvh",
          long_options, 0)) != EOF){

    switch (c)
    {
      case 'a':
        actime=1;
        break;

      case 'c':
        no_create=1;
        break;

      case 'm':
        mdtime=1;
        break;

      case 'v':
        pversion();
        exit (0);

      case 'h':
        usage();
        exit (0);

      case '?':
        if (optopt == 'c'){
          fprintf (stderr, "Option -%c requires an argument.\n", optopt);
          try_help(0);
        }
        else if (isprint (optopt)){
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
          try_help(0);
        }
        else {
          fprintf (stderr,
                    "Unknown option character `\\x%x'.\n",
                    optopt);
          try_help(0);
        }
        return 1;

        default:
          try_help (0);
      }
  }
  if (optind >= argc) {
    try_help("Expected file argument after options");
  }
  else{
    for (index=0; optind < argc; index++){
      file = fopen(argv[optind], "rb+");
      if(file == NULL && !no_create){
        file = fopen(argv[optind], "w");
        fclose(file);
      } else if (file != NULL) {
        fclose(file);
        change_time(argv[optind]);
      }
      optind++;
    }
  }
  return 0;
}
