#include <stdio.h>
#include <stdlib.h>
#ifdef DOUBLE
#include "dlists.h"
#else
#include "slists.h"
#endif

person* insert_start(person* people, char *name, int age, char *info, int person_type)
{

  struct person* pTemp = malloc(sizeof(person));  

  // put name and age into the next free place in the array parameter here
  pTemp->name = name;
  pTemp->age = age;
  pTemp->staff_or_student = person_type;
  pTemp->pPrevious = NULL;
  if(person_type == 1)
  	pTemp->extraInfo.programme_name = info;
  else if(person_type == 0)
  	pTemp->extraInfo.room_number = info;
  pTemp->pNext = people;

  if (people != NULL)
     people->pPrevious = pTemp;
  return pTemp;
}


person* insert_end(person* people, char *name, int age, char *info, int person_type)
{
  struct person* temp = people;
  struct person* pTemp = malloc(sizeof(person));  

  // put name and age into the next free place in the array parameter here
  pTemp->name = name;
  pTemp->age = age;
  pTemp->staff_or_student = person_type;
  
  if(person_type == 1)
  	pTemp->extraInfo.programme_name = info;
  else if(person_type == 0)
  	pTemp->extraInfo.room_number = info;
  pTemp->pNext = NULL;
  if (people == NULL) {
    return pTemp;
  }
  while (temp->pNext != NULL){
  	temp = temp->pNext;

  }
  temp->pNext = pTemp;

  return people;
}

person* insert_sorted(person* people, char *name, int age,int compare_people(person* old, person* new), char *info, int person_type)
{
  struct person* current = people;
  struct person* previous;
  struct person* pTemp;
  pTemp = malloc(sizeof(person));  

  // put name and age into the next free place in the array parameter here
  pTemp->name = name;
  pTemp->age = age;
  pTemp->staff_or_student = person_type;
  if(person_type == 1)
  	pTemp->extraInfo.programme_name = info;
  else if(person_type == 0)
  	pTemp->extraInfo.room_number = info;
  pTemp->pNext = NULL;
  if (people == NULL || compare_people(current, pTemp)<0) {
  	pTemp->pNext = people;
    return pTemp;
  } 
  else {
    previous = people;
    current = current->pNext;

    while (current != NULL && compare_people(current, pTemp)>=0){
      previous = current;
      current = current->pNext;
    }

    pTemp->pNext = current;
    previous->pNext = pTemp;
  }
  return people;
}

