// Program that sorts array via bubble sort.

#include <stdlib.h>   // Libraries which are needed
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) 
{
  // Number of elements
  int n;
  scanf("%d", &n);

  int i=0, j=0;
  // Initialize unsorted  array
//int* unsortedArray = malloc(n * sizeof(int));
  int unsortedArray[1000000];
  char temp;
  // Take input numbers while i is not equal number of elements and
  // put them in the array
  do {
      scanf("%d%c", &unsortedArray[i], &temp);
      i++;
  } while(temp != '\n' && i != n);
  
  // Initialize temporary value
  int swap;
  int swapped;
  // do while numbers are swapping
  do {
    // Value to check if the numbers were swapped
    swapped = 0;
    // Go through array from 0 to length - 2
    for (j = 0; j < i - 1; j++){
      if (unsortedArray[j] > unsortedArray[j + 1]){
        swap = unsortedArray[j];
        unsortedArray[j] = unsortedArray[j + 1];
        unsortedArray[j + 1] = swap;
        swapped = 1;
      }
    }
  }while(swapped == 1);
  
  // Print
  for(j=0; j<i; j++) {
    printf("%d ", unsortedArray[j]);
  }
    
  return 0;
}
