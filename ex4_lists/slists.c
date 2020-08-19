#include <stdio.h>
#include <stdlib.h>
#include "slists.h"

person* insert_start(person* people, char *name, int age, char *info, int person_type)
{
  // Allocate memory for a new node
  struct person* pTemp = malloc(sizeof(person));  
  if (pTemp != NULL) {
    // put name and age into the next free place in the array parameter here
    pTemp->name = name;
    pTemp->age = age;
    pTemp->staff_or_student = person_type;
    if(person_type == 1)
    	pTemp->extraInfo.programme_name = info;
    else if(person_type == 0)
    	pTemp->extraInfo.room_number = info;
    pTemp->pNext = people;
    // Return beginning of the list
    return pTemp;
  }
  exit(0);
}


person* insert_end(person* people, char *name, int age, char *info, int person_type)
{
  struct person* temp = people;
  struct person* pTemp = malloc(sizeof(person));  
  if (pTemp != NULL) {
  // put name and age into the next free place in the array parameter here
  pTemp->name = name;
  pTemp->age = age;
  pTemp->staff_or_student = person_type;
  if(person_type == 1)
  	pTemp->extraInfo.programme_name = info;
  else if(person_type == 0)
  	pTemp->extraInfo.room_number = info;
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
  }
  // Return beginning
  return people;
}

person* insert_sorted(person* people, char *name, int age,int (*compare_people)(person* old, person* new), char *info, int person_type)
{
  //Current and previous nodes
  struct person* current = people;
  struct person* previous;
  struct person* pTemp;
  // Allocate memory for a new node
  pTemp = malloc(sizeof(person));  
  if (pTemp != NULL) {
  // put name and age into the next free place in the array parameter here
  pTemp->name = name;
  pTemp->age = age;
  pTemp->staff_or_student = person_type;
  if(person_type == 1)
  	pTemp->extraInfo.programme_name = info;
  else if(person_type == 0)
  	pTemp->extraInfo.room_number = info;
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
      // Update
      previous = current;
      current = current->pNext;
    }
    //set the new person ’ s ∗next∗ link to  point  to  the  next  item  in  the  list
    pTemp->pNext = current;
    // set the *next∗ link of this item to point to the new person
    previous->pNext = pTemp;
  }
  }
  // Return beginning of the list
  return people;
}


