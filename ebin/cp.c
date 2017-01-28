/*! \file cp.c
 *  \author Grzegorz Jaworski
 *  \date 28 Styczeń 2017
 *  \version   v0.1
 *  \brief Kopiowanie pliku do innej lokacji
 *  \details Program kopiujący wskazany plik do innej lokacji.
 *  @see https://github.com/HiImTrixie/shell-jj
 *
 *
 *
 */

int main(int argc, char **argv)
{
        FILE *file1= NULL, *file2= NULL;
        if(argv[1] && argv[2])
        {
                fp1 = fopen(argv[1], "r");
                fp2 = fopen(argv[2], "w");
                char symbol;
                for(int i=0; ( symbol = fgetc(file1)) != -1; i++)
                  fputc(symbol, file2);
                fclose(file1);
                fclose(file2);
        }
        else
        {
                fprintf(stderr, "Not enough or too many arguments\n");
        }
	return 0;
}
