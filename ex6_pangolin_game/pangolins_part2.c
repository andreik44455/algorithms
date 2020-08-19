// Panglolins game
// More interactive version where it gets input from the user 
// and then building new parts of the tree in response to what the user says.

#include <stdlib.h>   // Libraries which are needed
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define BUFSIZE 80
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
  }
}// printNode

void treePrint(struct node* nod){
  if (nod == NULL){

  }
  else{
  	if (nod -> object_or_quest == 1){
      printNode(nod);
  	  treePrint(nod -> yes_ptr);
  	  treePrint(nod -> no_ptr);
    } else {
      printNode(nod);
    }
  }
}// treePrint



node* treeCompare(struct node* nod, struct node* compNode){
  if (nod == NULL){

  }
  else{
    struct node* found = nod;
    if (nod->object_or_quest == 1)
    {
      if(nod->yes_ptr == compNode){
        return nod;
      }
      else if (nod->no_ptr == compNode){
        return nod;
      }
      found = treeCompare(nod->yes_ptr, compNode);

      if(found == NULL){
      
      found = treeCompare(nod->no_ptr, compNode);
        return found;
      }else {
        return found;
      }
    }
  }
}// treeCompare

node* insertQuestion(node* nodes, node* currentNode, char* question, char* name, char* answer)
{
  struct node* begin = nodes;
  struct node* pTemp;
  struct node* pObject;
 
  // Allocate memory for a new node
  pTemp = malloc(sizeof(node));  
  pObject = malloc(sizeof(node));
  pObject->object_or_quest = 0;
  pObject->extraInfo.object_name = name;
  if (pTemp != NULL) {
  // put name and age into the next free place in the array parameter here
  pTemp->object_or_quest = 1;
  pTemp->extraInfo.question = question;

  
  if (nodes->object_or_quest == 0){
    if (cmp(answer) == 0){
      pTemp->yes_ptr = pObject;
      pTemp->no_ptr = currentNode;
      return pTemp;
    } else if(cmp(answer) == -1){
      pTemp->yes_ptr = currentNode;
      pTemp->no_ptr = pObject;
      return pTemp;
    }  
  }
  begin = treeCompare(begin, currentNode);
  
  if (cmp(answer) == 0){
    pTemp->yes_ptr = pObject;
    pTemp->no_ptr = currentNode;
  } else if(cmp(answer) == -1){
    pTemp->yes_ptr = currentNode;
    pTemp->no_ptr = pObject;
  }  
  
  if (begin->yes_ptr == currentNode){
    begin -> yes_ptr = pTemp;
  } else if (begin->no_ptr == currentNode){
    begin -> no_ptr = pTemp;
  }

  // Return beginning of the list
  return nodes;
  }
}

int cmp(char *answer){
    if(strcmp(answer, "yes") == 0 || strcmp(answer, "absolutely") == 0 || strcmp(answer, "y") == 0 ||
       strcmp(answer, "Correct") == 0 || strcmp(answer, "Yes") == 0){
      return 0;
    } 
    else if (strcmp(answer, "no") == 0 || strcmp(answer, "No") == 0 || strcmp(answer, "n") == 0 ||
             strcmp(answer, "NO") == 0){
      return -1;
    }
    else{
      return 1;
    }
}

void freeTree(node* nod){
  if (nod == NULL){

  }
  else{
    if (nod -> object_or_quest == 1){
      freeTree(nod -> yes_ptr);
      freeTree(nod -> no_ptr);
      free(nod->extraInfo.question);
      free(nod);
    } else {
     free(nod->extraInfo.object_name);
      free(nod);
    }
  }
}

int main(int argc, char **argv) 
{
  // Declare strings for object and question
  char *object;
  char *question;
  char* new;
  // Declare nodes array here 
  struct node* nodes = NULL;
  // Initialize first object
  struct node* initial_object = malloc(sizeof(node));
  char *firstName = malloc(sizeof(char*)*12);
  strncpy(firstName, "a pangoline", 12);
  initial_object->object_or_quest = 0;
  initial_object->extraInfo.object_name = firstName;
  // Now tree has the first object
  nodes = initial_object;
  struct node* currentNode = nodes;
  char* answer = malloc(sizeof(char*));
  

  
  int finished = 1;
  while(finished == 1){
    // If current node is a leaf...
    if(currentNode->object_or_quest == 0){
      // Make the guess
      printf("Is it %s?\n", currentNode->extraInfo.object_name);
      scanf("%s", answer);
      while (cmp(answer) != 0 && cmp(answer) != -1){
          printf("Enter yes or no.\n");
          scanf("%s", answer);
      }
      // If user says yes...
      if (cmp(answer) == 0){
        // Computer has won
        printf("Good\n");
      }
      // else user has won
      else if (cmp(answer) == -1){
       
        // Get a new object
        printf("you win. What were you thinking of?\n");
        object = malloc(sizeof(char*)*BUFSIZE);
        fgets(object, BUFSIZE, stdin);
        fgets(object, BUFSIZE, stdin);
        object[strlen(object)-1]='\0';
        if(strncmp(object, "a ", strlen("a ")) != 0 && strncmp(object, "an ", strlen("an ")) != 0 &&
           strncmp(object, "the ", strlen("the ")) != 0 && strncmp(object, "A ", strlen("A ")) != 0){
          new = malloc(sizeof(char*)*strlen(object));
          strcpy(new, object);
          strcpy(object, "a ");
          strcat(object, new);
          free(new);
        }  
        // Get a question for object
        printf("Please give me a question about %s, so I can tell the difference between %s and %s\n", object, object, currentNode->extraInfo.object_name);
        question = malloc(sizeof(char*)*BUFSIZE);
        fgets(question,BUFSIZE,stdin);
        question[strlen(question)-1]='\0';
        
        if(strcmp(&question[strlen(question)-1], "?") != 0){
          question[strlen(question)] = '?';
        }

        printf("What is answer for %s?\n", object);
        scanf("%s", answer);
        while (cmp(answer) != 0 && cmp(answer) != -1){
          printf("Enter yes or no.\n");
          scanf("%s", answer);
        }  
       
        nodes = insertQuestion (nodes, currentNode, question, object, answer);
        
      }
      finished = 0;
      printf("Do you want to play again?\n");

      scanf("%s", answer);
      while (cmp(answer) != 0 && cmp(answer) != -1){
        printf("Enter yes or no.\n");
        scanf("%s", answer);
      }  
      if (cmp(answer) == 0){
        finished = 1;
        currentNode = nodes;
      }
    } 
    else {
      printf("%s\n", currentNode->extraInfo.question);
      scanf("%s", answer);
      while (cmp(answer) != 0 && cmp(answer) != -1){
          printf("Enter yes or no.\n");
          scanf("%s", answer);
      }
      // Set current node according to Yes/No response
      if (cmp(answer) == 0){
        currentNode = currentNode->yes_ptr;
      } 
      else if(cmp(answer) == -1){
        currentNode = currentNode->no_ptr;
      }
    }
  }    
  free(answer);
  freeTree(nodes);
  
  return 0;
}
