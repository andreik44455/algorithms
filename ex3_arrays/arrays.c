#include <stdio.h>
#include <stdlib.h>
#include "arrays.h"

/* declare your struct for a person here */
typedef struct person {
  char* name;
  int age;
} person;

static void insert(person* people[HOW_MANY], char *name, int age, int *nextfreeplace) 
{
  people[*nextfreeplace] = malloc(sizeof(person));  

  /* put name and age into the next free place in the array parameter here */
  people[*nextfreeplace]->name = name;
  people[*nextfreeplace]->age = age;
  /* modify nextfreeplace here */
  (*nextfreeplace)++;
  
}

int main(int argc, char **argv) 
{

  /* declare the people array here */
  struct person* people[HOW_MANY];
  int nextfreeplace = 0;
  int i;
  for (i = 0; i < HOW_MANY; i++) 
  {
    insert (people, names[i], ages[i], &nextfreeplace);
  }

  /* print the people array here*/
  for (i = 0; i < HOW_MANY; i++) 
  {
    printf("%d: %s is %d\n", i, people[i]->name, people[i]->age);
  }

  for (i = 0; i < HOW_MANY; i++) {
    free(people[i]);
  }

  return 0;
}
