/*! \file man.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.3
 *  \brief Wyświetl dokumentacje funkcji
 *  \details Program wyświetlający dokumentacje wskazanego pliku jako argument.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // library with isprint()
#include <getopt.h>

char version[64] = "v.0.3"; /*!< Aktualna wersja programu */

unsigned cman = 0; /*!< Wyświetl dokumentacje dla języka c */

// Content of help
static char const * const option_help[] =
{
"Some of useful options.\n\n",
"  -c --cman  Show manual with c.",
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
  {"cman", 0, 0, 'c'},
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
  printf ("Usage: man [OPTION]... [FILE]...\nShows manual for inserted function.\n\n");
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
  printf ("Try 'man --help' for more information.\n");
  exit(EXIT_FAILURE);
}

/*! \brief Funkcja wyświetla aktualna wersje programu.
 *
 * Funkcja wyświetla wersje programu po podaniu jako argumentu -v oraz zamyka program.
 */
void pversion()
{
  printf ("Man\nVersion: %s\n", version);
  exit(-1);
}

/*! \brief Funkcja wyświetlająca dokumentacje.
 *
 * Funkcja wyświetlająca dokumentacje dla podanej funkcji jeżeli takowa istnieje.
 *
 * \param[in] *name Nazwa funkcji poszukiwanej dokumentacji.
 */
void read_(char *name)
{
  FILE *file;
	int c;
  char dest[64]="../man/";
  if (cman)
    strcat(dest,"2/");
  strcat(dest,name);
  strcat(dest,".txt");
  file = fopen(dest, "r");
  if(file)
  {
    while((c = getc(file)) != EOF)
      putchar(c);
    fclose(file);
  }else{
    printf("No manual entry for %s\n", name );
  }
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
      case 'c':
        cman=1;
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
  if ( optind == argc){
    try_help("What manual page do you want read?");
  }
  else if (optind >= argc) {
    try_help("Expected argument after options");
  }
  else if (argc - optind < 1){
    try_help("Insert one more argument after options");
  }
  else if (argc - optind > 1){
    try_help("Inserted more than two arguments");
  }
  else{
    read_(argv[optind]);
  }
	return 1;
}
