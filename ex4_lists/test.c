#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "slists.h"
#include "printing.h"
#include "data.h"



int compare_people_by_name(person* old, person* new){
  return strcmp(new->name, old->name);
}
int compare_people_by_age(person* old, person* new){
    int new_age = new->age;
    int old_age = old->age;
    if (new_age < old_age){
      return -1;
    } else if(new_age > old_age){
    return 1;
  } else return 0;
}


int main(int argc, char **argv) 
{

  /* declare the people array here */
  struct person* people = NULL;
  int i;
  
  // if first argument is equal to insert_start or 1 argument
  if (argc == 1 || (strcmp(argv[1], "insert_start")==0)) {
    for (i = 0; i < HOW_MANY; i++) 
    {
      people = insert_start (people, names[i], ages[i], info[i], person_type[i]);
    }
  } 
  // if first argument is equal to insert_end and 2 arguments
  else if (argc == 2 && strcmp(argv[1], "insert_end")==0) {
    for (i = 0; i < HOW_MANY; i++) 
    {
      people = insert_end (people, names[i], ages[i], info[i], person_type[i]);
    }
  } 
  // if first argument is equal to insert_sorted and 2 arguments
  else if (argc == 2 && strcmp(argv[1], "insert_sorted")==0) {
    for (i = 0; i < HOW_MANY; i++) 
    {
      people = insert_sorted (people, names[i], ages[i], &compare_people_by_name, info[i], person_type[i]);
    }
  }
  // if first argument is equal to insert_sorted and 2 arguments
  else if (argc == 3 && strcmp(argv[1], "insert_sorted")==0){
    // if second argument is age
    if (strcmp(argv[2], "age")==0){
      for (i = 0; i < HOW_MANY; i++) 
      {
        people = insert_sorted (people, names[i], ages[i], &compare_people_by_age, info[i], person_type[i]);
      }
    } else {
    	fprintf(stderr, "Wrong 2nd argument\n");
  	return 1;
    } 
  }
  else {
  	fprintf(stderr, "unrecognised/unexpected command-line options are given\n");
  	return 1;
  }  
  // Create temporary structure
  struct person* tmp;
  while (people != NULL)
   {
     // Update
     tmp = people;
     // Print structure
     printData(people);
     // Update 
     people = people->pNext;
     // Free
     free(tmp);
   }

  return 0;
}
