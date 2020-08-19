// Panglolins game
// Basic Structure
// Game plays itself: hard coded tree of questions and answers 

#include <stdlib.h>   // Libraries which are needed
#include <stdio.h>
#include <string.h>
union data {
   char* object_name;
   char* question;
};

enum type{object, question};

typedef struct node {
  enum type object_or_quest;
  union data extraInfo;
  struct node *yes_ptr;
  struct node *no_ptr;
} node;

void printNode(struct node* nod) {
  if (nod -> object_or_quest == 0){
    printf("Object: %s \n", nod -> extraInfo.object_name);
  }  
  else {  
    printf("Question: %s \n", nod -> extraInfo.question);
    printf("Yes: %s \n", nod -> yes_ptr -> extraInfo.object_name);
    printf("No: %s \n", nod -> no_ptr -> extraInfo.object_name);
  } 
  
}

void treePrint(struct node* nod){
  if (nod == NULL){

  }
  else{
  	printNode(nod);
  	if (nod -> object_or_quest == 1){
  	  treePrint(nod -> yes_ptr);
  	  treePrint(nod -> no_ptr);
    }
  }
}

int main(int argc, char **argv) 
{
  
  struct node nodes[13];
  nodes[0].object_or_quest = 1;
  nodes[0].extraInfo.question = "Does it have a tail?";
  nodes[0].yes_ptr = &nodes[1];
  nodes[0].no_ptr = &nodes[8];

  nodes[1] . object_or_quest = 1;
  nodes[1] . extraInfo.question = "Does it like to  chase mice?";
  nodes[1] . yes_ptr = &nodes[2];
  nodes[1] . no_ptr = &nodes[3];

  nodes[2] . object_or_quest = 0;
  nodes[2] . extraInfo.object_name = "cat";

  nodes[3] . object_or_quest = 1;
  nodes[3] . extraInfo.question = "Is it barking?";
  nodes[3] . yes_ptr = &nodes[4];
  nodes[3] . no_ptr = &nodes[5];

  nodes[4] . object_or_quest = 0;
  nodes[4] . extraInfo.object_name = "dog";

  nodes[5] . object_or_quest = 1;
  nodes[5] . extraInfo.question = "Is it the biggest mammal?";
  nodes[5] . yes_ptr = &nodes[6];
  nodes[5] . no_ptr = &nodes[7];

  nodes[6] . object_or_quest = 0;
  nodes[6] . extraInfo.object_name = "whale";

  nodes[7] . object_or_quest = 0;
  nodes[7] . extraInfo.object_name = "pangolin";

  nodes[8] . object_or_quest = 1;
  nodes[8] . extraInfo.question = "Is it flat, round and edible?";
  nodes[8] . yes_ptr = &nodes[9];
  nodes[8] . no_ptr = &nodes[12];

  nodes[9] . object_or_quest = 1;
  nodes[9] . extraInfo.question = "Can you dip it in your tea?";
  nodes[9] . yes_ptr = &nodes[10];
  nodes[9] . no_ptr = &nodes[11];

  nodes[10] . object_or_quest = 0;
  nodes[10] . extraInfo.object_name = "biscuit";

  nodes[11] . object_or_quest = 0;
  nodes[11] . extraInfo.object_name= "pizza";

  nodes[12] . object_or_quest = 0;
  nodes[12] . extraInfo.object_name = "Pete";
  int i;
  for(i=0; i < sizeof(nodes)/sizeof(*nodes); i++){
  	printNode(&nodes[i]);
  }
  
  treePrint(nodes);


  return 0;
}