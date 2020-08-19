/* Program to convert from  Celsius to Fahrenheit
 * and vice versa. Takes 2 input arguments.
 * 1st - c2f or f2c. 2nd - number. 
 */
#include <stdlib.h>		// Libraries which are needed
#include <stdio.h>
#include <string.h>

void c2f (float c);
void f2c (float f);

int main (int argc, char *argv[]) {
  int ii;
  float temp;
  // Check number of args
  if (argc != 3){
    printf("The wrong number of parameters have been supplied\n");
    exit(1);
  } 
  // Check the second parameter
  else if (strcmp(argv[1], "-c") && strcmp(argv[1], "-f")){
    printf("Failed to supply either -f or -c as the first option\n");
    exit(2);
  } 
  // Check whether given number is float
  else if (sscanf(argv[2],"%f", &temp) != 1) {
    printf("Malformed number\n");
    exit(3);
  } 
  // Check whether 2nd arg has only digits, . and -
  char* str = argv[2];
  size_t span = strspn(str, "0123456789.-");
  if(!(str[span] == '\0')) {
    printf("The string has to have only numbers and '.'!\n");
    exit(3);
  }

  // Check how to convert and call the method to do it
  if (strcmp(argv[1], "-c") == 0) {
    if (temp < -273.15) {
      printf("Temperatures below absolute zero\n");
      exit(4);
    }
    c2f(temp);
  }
  else {
    if(temp < -459.67) {
     printf("Temperatures below absolute zero\n");
     exit(4);
    }
    f2c(temp);
  }  

  exit(0);
}

// Convert from celc to far
void c2f (float c) {
  float f;
  f = 9*c/5 + 32;
  printf("%3.2f°C = %3.2f°F\n", c, f);
}

// Convert from far to cel
void f2c (float f){
  float c;
  c = 5*(f - 32)/9;
  printf("%3.2f°C = %3.2f°F\n", c, f);
}

/*----------------------------------------------------------------------------*/
