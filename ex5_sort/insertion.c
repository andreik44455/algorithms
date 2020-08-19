// Program that sorts array via insertion sort.

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
  int current;
  // Go through array from 1 to length-1
  for(j = 1; j < n; j++){
    // Update the current value
    current = unsortedArray[j];
    // Update the previous value
    i = j - 1;
    // While previous value's index is more than 0
    // and current is less than previous value - swap
    while(i >= 0 && current < unsortedArray[i]){
      swap = unsortedArray[i];
      unsortedArray[i] = unsortedArray[i+1];
      unsortedArray[i+1] = swap;
      i--;
    }
  }

  for(j=0; j<n; j++) {
    printf("%d ", unsortedArray[j]);
  }
    
  return 0;
}
