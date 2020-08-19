// Read input file from standart input, convert all lower-case
// to upper-case and vice versa, write it to the ouput file.
#include <stdlib.h>		// Libraries which are needed
#include <stdio.h>
#include <ctype.h>

/*----------------------------------------------------------------------------*/
// The 'root' programme; execution start
int main ()	
{
  char input[100];
  char output[100];
  printf("Enter input file name\n");
  scanf("%s", input);
  printf("Enter output file name\n");
  scanf("%s", output); 

  FILE *fp;
  fp = fopen(input,"r");
  FILE *out_file;
  out_file = fopen(output, "w");

  if (fp == NULL || out_file == NULL) {
      perror("Error in opening file");
      exit(0);
  }
  
  int countUp = 0;
  int countLow = 0;

  char c = fgetc(fp); 
  int countChar = 0;
  while (c != EOF)  { 
    if (isupper(c)) {
      fputc(tolower(c), out_file);
      countLow++;
    }  
    else if (islower(c)) {
      fputc(toupper(c), out_file);  
      countUp++;
    }
    else fputc(c, out_file);

    countChar++;

    c = fgetc(fp);
  } 
  
  fclose(fp); 
  fclose(out_file); 
  
  printf("\nRead %d characters in total, %d converted to upper-case, %d to lower-case\n",
         countChar, countUp, countLow);
  
  exit(0);
}
