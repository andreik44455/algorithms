//Find longest command line argument

#include <stdlib.h>		// Libraries which are needed
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
// The 'root' programme; execution start
int main (int argc, char *argv[])	
{
  int ii;

  if (argc == 1) {
    printf("Error: expected some command-line parameters\n");
    exit(0);
  }

  int max = 0;
  char *longest = "";
  // Iterate over arguments supplied
  for (ii = 1; ii < argc; ii++)	{
    if(strlen(argv[ii]) > max) {
      longest = argv[ii];
      max = strlen(argv[ii]);
    }
  }
  printf("%s\n", longest);

  exit(0);
}

/*----------------------------------------------------------------------------*/
