// Panglolins game
// Same as part2 but allows load and save games

#include <stdlib.h>   // Libraries which are needed
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define BUFSIZE 80
// For distinguishing between object and question
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

// Function for printing nodes
void printNode(struct node* nod, FILE * fp) {
  // If object
  if (nod -> object_or_quest == 0){
    fprintf(fp, "Object: %s \n", nod -> extraInfo.object_name);
  }  
  // else question
  else {  
    fprintf(fp, "Question: %s \n", nod -> extraInfo.question);
  }
}// printNode

// Function for printing a tree
void treePrint(struct node* nod, FILE * fp){
  if (nod == NULL){
  }
  else{
    // If question ...
    if (nod -> object_or_quest == 1){
      // Print it
      printNode(nod, fp);
      // Pting its pointers
      treePrint(nod -> yes_ptr, fp);
      treePrint(nod -> no_ptr, fp);
    // If object...  
    } else {
      // Print it
      printNode(nod, fp);
    }
  }
}// treePrint

// Function for reducing size of a line from saved file
void chopN(char *str, size_t n)
{
    size_t len = strlen(str);
    if (n > len)
        return;  // Or: n = len;
    memmove(str, str+n, len - n + 1);
}

// Function for reading a tree
node* treeRead(FILE *file){
  // Initialize string for getting an line from file
  char *line = malloc(sizeof(char*)*BUFSIZE);
  // Initialize node for question/object
  struct node* pTemp = malloc(sizeof(node)); 
  // Check if the end of a file
  if (feof(file)){
    return NULL;
  }else {
    // Get the line
    fgets(line, BUFSIZE, file);
    // Reduce its size
    line[strlen(line)-1]='\0';
    // If question...
    if(strncmp(line, "Question: ", strlen("Question: ")) == 0){
      // Delete first word
      chopN(line, 10);
      // Fill a node
      pTemp->object_or_quest = 1;
      pTemp->extraInfo.question = line;
      // Call treeRead to fill its pointer
      pTemp->yes_ptr = treeRead(file);
      pTemp->no_ptr = treeRead(file);
    } else {
      // If object...
      if(strncmp(line, "Object: ", strlen("Object: ")) == 0){
        chopN(line, 8);
        pTemp->object_or_quest = 0;
        pTemp->extraInfo.object_name = line;
      }
    }
  }
  return pTemp;
}

// Function for finding parent of currentNode
node* treeCompare(struct node* nod, struct node* compNode){
  if (nod == NULL){

  }
  else{
    // Initialize a node
    struct node* found = nod;
    // If question
    if (nod->object_or_quest == 1)
    {
      // Check its pointers
      if(nod->yes_ptr == compNode){
        return nod;
      }
      else if (nod->no_ptr == compNode){
        return nod;
      }
      // If haven't found check its poiter
      found = treeCompare(nod->yes_ptr, compNode);
      // nothing was found
      if(found == NULL){
      // Check another pointer
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
  // Begin has root pointer
  struct node* begin = nodes;
  // Decalare nodes for question and object
  struct node* pTemp;
  struct node* pObject;
 
  // Allocate memory for new nodes
  pTemp = malloc(sizeof(node));  
  pObject = malloc(sizeof(node));
  pObject->object_or_quest = 0;
  pObject->extraInfo.object_name = name;
  if (pTemp != NULL) {
  // put name and age into the next free place in the array parameter here
  pTemp->object_or_quest = 1;
  pTemp->extraInfo.question = question;

  // If root is object
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
  // Look for parent of current node
  begin = treeCompare(begin, currentNode);
  // Place pointers for question depending on answer from user
  if (cmp(answer) == 0){
    pTemp->yes_ptr = pObject;
    pTemp->no_ptr = currentNode;
  } else if(cmp(answer) == -1){
    pTemp->yes_ptr = currentNode;
    pTemp->no_ptr = pObject;
  }  
  // Place question in the tree
  if (begin->yes_ptr == currentNode){
    begin -> yes_ptr = pTemp;
  } else if (begin->no_ptr == currentNode){
    begin -> no_ptr = pTemp;
  }

  // Return beginning of the list
  return nodes;
  }
}

// Function for checking input
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
  char *object, buffer[BUFSIZE];
  char *question;
  char* new;
  // Initialize filename and answer strings
  char* answer = malloc(sizeof(char*));
  char *filename = malloc(sizeof(char*));
  // Declare nodes array here 
  struct node* nodes = NULL;
  // Ask if player want to load a game
  printf("Do you want to load a game?\n");
  // Get his input
  scanf("%s", answer);
  // Check if valid
  while (cmp(answer) != 0 && cmp(answer) != -1){
    printf("Enter yes or no.\n");
    scanf("%s", answer);
  }
  // If no...
  if(cmp(answer) == -1){
    // Initialize first object
    struct node* initial_object = malloc(sizeof(node));
    char *firstName = malloc(sizeof(char*)*12);
    strncpy(firstName, "a pangoline", 12);
    initial_object->object_or_quest = 0;
    initial_object->extraInfo.object_name = firstName;
    // Now tree has the first object
    nodes = initial_object;
  } 
  // If no...
  else if (cmp(answer) == 0){
    // Ask the name of a file
    printf("Enter the name of a file\n");
    // Get the name
    scanf("%s", filename); 
    FILE *file = fopen(filename, "r");
    // Create tree
    nodes = treeRead(file);
    fclose(file);
  }  
  // Current node at the root of the tree
  struct node* currentNode = nodes;
  
  int finished = 1;
  // While game is not finished...
  while(finished == 1){
    // If current node is a leaf...
    if(currentNode->object_or_quest == 0){
      // Make the guess
      printf("Is it %s?\n", currentNode->extraInfo.object_name);
      // Get input
      scanf("%s", answer);
      // Check if valid
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
       
        // Ask for an object
        printf("you win. What were you thinking of?\n");
        // Initialize object's name
        object = malloc(sizeof(char*)*BUFSIZE);
        // Read empty afte scanf
        fgets(object, BUFSIZE, stdin);
        // Get object's name
        fgets(object, BUFSIZE, stdin);
        // Cut the name
        object[strlen(object)-1]='\0';
        // Check if valid, if no - add article
        if(strncmp(object, "a ", strlen("a ")) != 0 && strncmp(object, "an ", strlen("an ")) != 0 &&
           strncmp(object, "the ", strlen("the ")) != 0 && strncmp(object, "A ", strlen("A ")) != 0){
          new = malloc(sizeof(char*)*strlen(object));
          strcpy(new, object);
          strcpy(object, "a ");
          strcat(object, new);
          free(new);
        }  
        // Ask for question for the object
        printf("Please give me a question about %s, so I can tell the difference between %s and %s\n", object, object, currentNode->extraInfo.object_name);
        // Initialze question string        
        question = malloc(sizeof(char*)*BUFSIZE);
        // Get input
        fgets(question,BUFSIZE,stdin);
        question[strlen(question)-1]='\0';
        // Check if valid
        if(strcmp(&question[strlen(question)-1], "?") != 0){
          question[strlen(question)] = '?';
        }
        // Ask for an answer for the question
        printf("What is answer for %s?\n", object);
        scanf("%s", answer);
        // Check if valid
        while (cmp(answer) != 0 && cmp(answer) != -1){
          printf("Enter yes or no.\n");
          scanf("%s", answer);
        }  
        // Insert new question and object
        nodes = insertQuestion (nodes, currentNode, question, object, answer);
        
      }
      // If the end of a round ask for continuing
      finished = 0;
      printf("Do you want to play again?\n");

      scanf("%s", answer);
      while (cmp(answer) != 0 && cmp(answer) != -1){
        printf("Enter yes or no.\n");
        scanf("%s", answer);
      }  
      if (cmp(answer) == 0){
        finished = 1;
        // Return current node to the root
        currentNode = nodes;
      }
    } 
    else {
      // If question...
      // Print question
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
  // Ask whether player wants to save a game
  printf("Do you want to save a game?\n");
  scanf("%s", answer);
  while (cmp(answer) != 0 && cmp(answer) != -1){
    printf("Enter yes or no.\n");
    scanf("%s", answer);
  }
  // Save
  if(cmp(answer) == 0){
    FILE * fp;
    printf("Enter the name of a file\n");
    scanf("%s", filename); 
    fp = fopen(filename, "w");
    treePrint(nodes, fp); 
    fclose(fp);
  }  
  free(filename);
  free(answer);
  freeTree(nodes);
  
  return 0;
}
