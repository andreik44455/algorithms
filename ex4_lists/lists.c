#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

/* declare your struct for a person here */
typedef struct person {
  char* name;
  int age;
  struct person *pNext;
} person;

static person* insert_start(person* people, char *name, int age) 
{
  // Allocate memory for a new node
  struct person* pTemp = (struct person*) malloc(sizeof(person));  
  if (pTemp != NULL) {
    // put name and age into the next free place in the array parameter here
    pTemp->name = name;
    pTemp->age = age;
    pTemp->pNext = people;
    // Return beginning of the list
    return pTemp;
  }
  exit(0);
}


static person* insert_end(person* people, char *name, int age) 
{
  // Pointer to current node
  struct person* temp = people;
  // Allocate memory for a new node
  struct person* pTemp = (struct person*) malloc(sizeof(person));  
  if (pTemp != NULL) {
    // put name and age into the next free place in the array parameter here
    pTemp->name = name;
    pTemp->age = age;
    pTemp->pNext = NULL;
    // Check whether current is null
    if (people == NULL) {
      return pTemp;
    }
    // While next pointer is not null
    while (temp->pNext != NULL){ 
        // Update
       	temp = temp->pNext;
    }
    // Update the next pointer
    temp->pNext = pTemp;

    return people;
  }
  exit(0);
}

//  Procedure to compare people by name
static int compare_people_by_name(person* old, person* new){
	return strcmp(new->name, old->name);
}

//  Precedure to compare people by age
static int compare_people_by_age(person* old, person* new){
    int new_age = new->age;
    int old_age = old->age;
    if (new_age < old_age){
      return -1;
    } else if(new_age > old_age){
	  return 1;
	} else return 0;
}


static person* insert_sorted(person* people, char *name, int age,int compare_people(person* old, person* new)) 
{
  //Current and previous nodes
  struct person* current = people;
  struct person* previous;
  // Allocate memory for a new node
  struct person* pTemp = (struct person*) malloc(sizeof(person));  
  if (pTemp != NULL) {
    // put name and age into the next free place in the array parameter here
    pTemp->name = name;
    pTemp->age = age;
    pTemp->pNext = NULL;
    //if the lists empty or the new person is less than the first item
    if (people == NULL || compare_people(current, pTemp)<0) {
      pTemp->pNext = people;
      return pTemp;
    } 
    else {
      // Keep track of previous and current node
      previous = people;
      current = current->pNext;
      // use a loop to find the last item that is smaller than the new person
      while (current != NULL && compare_people(current, pTemp)>=0){
        previous = current;
        current = current->pNext;
      }
      //set the new person ’ s ∗next∗ link to  point  to  the  next  item  in  the  list
      pTemp->pNext = current;
      // set the *next∗ link of this item to point to the new person
      previous->pNext = pTemp;
    }
    // Return beginning of the list
    return people;
  }
  exit(0);
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
      people = insert_start (people, names[i], ages[i]);
    }
  }  
  // if first argument is equal to insert_end and 2 arguments
  else if (argc == 2 && strcmp(argv[1], "insert_end")==0) {
    for (i = 0; i < HOW_MANY; i++) 
    {
      people = insert_end (people, names[i], ages[i]);
    }
  } 
  // if first argument is equal to insert_sorted and 2 arguments
  else if (argc == 2 && strcmp(argv[1], "insert_sorted")==0) {
    for (i = 0; i < HOW_MANY; i++) 
    {
      people = insert_sorted (people, names[i], ages[i], &compare_people_by_name);
    }
  }
  // if first argument is equal to insert_sorted and 2 arguments
  else if (argc == 3 && strcmp(argv[1], "insert_sorted")==0){
    // if second argument is age
    if (strcmp(argv[2], "age")==0){
      for (i = 0; i < HOW_MANY; i++) 
      {
        people = insert_sorted (people, names[i], ages[i], &compare_people_by_age);
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
  //Create temporary structure
  struct person* tmp;
  while (people != NULL)
   {
     // Update
     tmp = people;
     // Print line
     printf("Name: %s, age: %d\n", tmp -> name, tmp -> age);
     // Update
     people = people->pNext;
     // Free
     free(tmp);
   }

  return 0;
}
