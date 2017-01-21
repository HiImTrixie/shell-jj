/*! \file diff.c
 *  \author Grzegorz Jaworski
 *  \date 9 Styczeń 2017
 *  \version   v1.1
 *  \brief Porównanie różnic w plikach
 *  \details Program porównywujący różnice w podanych plikach.
 *  @see https://github.com/gostekk/c
 *
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // library with isprint()
#include <getopt.h>

/*!
  \def MAX_LINE_IN_FILE
  Maksymalna możliwa ilość występujących linii w pliku.
*/
#define MAX_LINE_IN_FILE 6

/*!
  \def MAX_CHAR_IN_LINE
  Maksymalna możliwa ilość znaków w jednej linii.
*/
#define MAX_CHAR_IN_LINE 255

char file1[MAX_LINE_IN_FILE][MAX_CHAR_IN_LINE]; /*!< Lista zawierająca zawartość pierwszego pliku */
char file2[MAX_LINE_IN_FILE][MAX_CHAR_IN_LINE]; /*!< Lista zawierająca zawartość drugiego pliku */

unsigned show_mode = 0; /*!< Tryb wydruku */
char show_mode_list[2][2] = {'<','>','-','+'}; /*!< Lista znaków danego trybu */

char program_name[20]; /*!< Nazwa wywołanego programu */

unsigned show_all_lines = 0; /*!< Wyświetl wszystkie linie */

unsigned recursive = 0; /*!< Rekursywne porównanie plików do pierwszego argumentu */

unsigned print_file_same_flag = 0; /*!< Wyświetlenie wiadomości jeżeli pliki są takie same  */

char *output_file = NULL; /*!< Nazwa pliku wyjściowego */

// Content of help
static char const * const option_help[] =
{
"-a  --show-all  Show all lines contained in files.",
"nope -b  --ignore-space-change  Ignore changes in the amount of white space.",
"nope -B  --ignore-blank-lines  Ignore changes whose lines are all blank.",
"-r  --recursive  Recursively compare any subdirectories found.",
"-s  --report-identical-files  Report when two files are the same.",
"nope -c  -C NUM  --context[=NUM]  Output NUM (default 2) lines of copied context.",
"nope -u  -U NUM  --unified[=NUM]  Output NUM (default 2) lines of unified context.",
"--help  Output this help.",
0
};

/*! \brief Struktura zawierająca opcje programu.
 *
 *  Funcja zawierająca długie opcje pliku wywoływane przy pomocy podwójnego myślnika na przykład:--show-all .
 */
static struct option const long_options[] =
{
  {"show-all", 0, 0, 'a'},
  {"recursive", 0, 0, 'r'},
  {"report-identical-files", 0, 0, 's'},
  {"help", 0, 0, 'h'},
  {0, 0, 0, 0}
};

/*! \brief Funkcja kopiuje zawartość pliku do listy.
 *
 *  Funcja odpowiedzialna za przeczytanie podanego pliku oraz skopiowanie zawartości do podanej listy.
 *
 *  \param[in] *name Nazwa pliku z, którego ma zostać skopiowana zawartość
 *  \param[in] array Nazwa listy do której ma zostać skopiowana zawartość pliku
 */
void copyfrom(char *name, char array[0][MAX_CHAR_IN_LINE])
{
  FILE *file= NULL;
  file = fopen(name, "r");
  if (file == NULL)
    exit(EXIT_FAILURE);
  char buff[MAX_CHAR_IN_LINE-1];
  for(int i=0; fscanf(file, "%s", &array[i][0]) != -1 ; i++);
  fclose(file);
}

/*! \brief Funkcja wyświetla zawartość pomocy.
 *
 *  Funcja uruchamiana gdy użytkownik wpisze --help lub -h, wyświetla ona zawartość pomocy oraz przykładowe użycie.
 */
void usage()
{
  printf ("Usage: %s [OPTION]... FILE1 FILE2\n\n", program_name);
  for (int i=0 ; option_help[i] != 0; i++)
    printf ("  %s\n", option_help[i]);
  printf ("\nIf FILE1 or FILE2 is `-', read standard input.\n");
}

/*! \brief Funkcja (wyświetla błąd)* oraz podpowiedz użycia pomocy.
 *
 *  Funcja wyświetla aktualny błąd jeżeli takowy wystąpił oraz podpowiedz użycia komendy wyświetlającej pomoc.
 */
static void try_help (char const *reason)
{
  if (reason)
    fprintf (stderr, "%s \n", reason);
  printf ("Try `%s --help' for more information.\n", program_name);
  exit(EXIT_FAILURE);
}

/*! \brief Funkcja porównująca dwie podane listy.
 *
 *  Funcja porównująca elementy dwóch list oraz wyświetlająca elementy nie zawierające się w drugiej.
 *
 *  \param file1 lista podana do porównania.
 *  \param file2 lista podana do porównania .
 *  \param x znak danego trybu
 */
void cmp_then_print(char file1[][255], char file2[][255],char x)
{
  int i,j,control;
  for( i=0; file1[i][0] != 0; i++) {
    control = 0;
    for( j=0; file2[j][0] != 0; j++) {
      if( strcmp(file1[i],file2[j])==0){
        if (show_all_lines)
            printf("  %s\n", file1[i]);
        control = 1;
        break;
      }
    }
    if ( control == 0)
      printf("%c %s\n", x,file1[i]);
  }
}

/*! \brief Funkcja porównująca dwie podane listy.
 *
 *  Funcja porównująca elementy dwóch list oraz wyświetlająca elementy nie zawierające się w drugiej.
 *
 *  \param fname1 nazwa pierwszej pliku.
 *  \param fname2 nazwa drugiego pliku .
 */
void diff(char *fname1,char *fname2)
{
  int i,j, control;
  // Read and copy content from file to array
  copyfrom(fname1, file1);
  copyfrom(fname2, file2);

  if ( !memcmp(file1, file2, sizeof(file1)) || strcmp(fname1,fname2)==0){
    if ( print_file_same_flag == 1)
      printf("Files %s and %s are identical\n", fname1, fname2);
    return;
  }
  printf("Loking for differences in %s and %s\n\n", fname1, fname2);
  cmp_then_print(file1,file2,show_mode_list[show_mode][0]);
  printf("---\n");
  cmp_then_print(file2,file1,show_mode_list[show_mode][1]);
}

/*! \brief Główna funkcja programu.
 *
 *  Funcja wywołująca program oraz sprawdzająca czy użytkownik użył jakąś funkcje przy wywołaniu.
 *
 */
int main (int argc, char **argv)
{
  int c, index;
  strcpy(program_name,argv[0]);
  opterr = 0;

  while ((c = getopt_long (argc, argv,
          "c:arhs",
          long_options, 0)) != EOF){

    switch (c)
    {
      case 'a':
        show_all_lines = 1;
        show_mode = 1;
        break;

      case 'r':
        recursive = 1;
        break;

      case 'h':
        usage();
        exit (0);

      case 's':
        print_file_same_flag = 1;
        break;

      case 'c':
        output_file = optarg;
        break;

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
    try_help("Expected argument after options");
  }
  else if (argc - optind < 2){
    try_help("Insert one more argument after options");
  }
  else if (argc - optind > 2 && recursive == 0){
    try_help("Inserted more than two arguments but without -r option");
  }
  else{
    c = optind;
    for (index=0; optind < argc; index++){
      optind++;
      diff(argv[c],argv[optind]);
    }
  }
  return 0;
}
