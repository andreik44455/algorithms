// Program that sorts array via bucket sort.

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
  int unsortedArray[n];
  char temp;
  // Take input numbers while i is not equal number of elements and
  // put them in the array
  do {
      scanf("%d%c", &unsortedArray[i], &temp);
      i++;
  } while(temp != '\n' && i != n);
  
  // Initialize array of buckets
  int buckets[32768];
  // Declare each bucket to 0
  for (j = 0; j < 32768; j++){
    buckets[j] = 0;
  }

  // Store in each index of the array the number of number in the list of that value.
  for (j = 0; j < n; j++){
    (buckets[unsortedArray[j]])++;
  }
  
  // Return the ordered numbers to array
  for (j = 0, i = 0; j < 32768; j++)  
    for(; buckets[j] > 0; (buckets[j])--)
      unsortedArray[i++] = j;

  for(j=0; j<n; j++) {
    printf("%d ", unsortedArray[j]);
  }
  return 0;
}

