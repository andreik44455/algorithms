#include "graph.h"


#ifdef BFS
#define MODE 2
#endif 

#ifdef DFS
#define MODE 1
#endif
/* Program that finds  find the node with the largest out-degree
   which can be reached from the node with the smallest (non-zero)
   out-degree & count the number of nodes reachable from the node
   with the smallest (non-zero) outdegree in the undirected graph
   using BFS and DFS.
*/
// Andrei Korovin
// 13.02.2019

// Function that helps freeMemory() to free each edjacency list
int freeList(List *current){
  if (current->next != NULL){
    freeList(current->next);
    free(current);
  }else{
    free(current);
    return 0;
  }

}

// Function to free the memory
void freeMemory(Graph *mygraph) {
  int i;
  for(i = 1; i < mygraph->MaxSize; i++){
    free(mygraph->table[i].name);
    if (mygraph->table[i].outlist == NULL){

    }else {
      List* current;
      current = mygraph->table[i].outlist;
      freeList(current);      
    }	
  }
  free(mygraph->table);
}

// structure of the queue 
struct queue {
  int front;
  int rear;
  int *items; // actual queue
};

// Function to initialize the queue
struct queue* createQueue(int size) {
  struct queue* q = malloc(sizeof(struct queue));
  q->items = malloc(sizeof(int) * size);
  q->front = -1;  // empty queue with  
  q->rear = -1;
  return q;
}

// Function to insert in the queue
void insertQueue(struct queue* q, int value, int max){
  if(q->rear == max-1){
    // queue is full
  }
  else {
    // if queue is empty
    if(q->front == -1)
      q->front = 0;   // set it to 0
    q->rear++;  // increase the number of the tail
    // put the item in the end of the queue
    q->items[q->rear] = value; 
  }
}

// Function to check whether queue is empty
int isEmpty(struct queue* q) {
  if(q->rear == -1) 
    return 1;
  else 
    return 0;
}

// Function to take element out of the queue
int dequeue(struct queue* q){
  int item;
  if(isEmpty(q)){
      item = -1;
  }
  else{
    // take element from the front
    item = q->items[q->front];
    q->front++;
    if(q->front > q->rear){
      // reset queue as empty
      q->front = q->rear = -1;
    }
  }
  return item;
}

// Function to print the queue
void printQueue(struct queue *q) {
  int i = q->front;

  if(isEmpty(q)) {
    printf("Queue is empty");
  } else {
    printf("\nQueue contains: \n");
    for(i = q->front; i < q->rear + 1; i++) {
      printf("%d ", q->items[i]);
    }
	  printf("\n");
  }    
}


void BFSearch(struct Graph* mygraph, int n, int visited[]){
  // Get the size of the graph
  int size = mygraph->MaxSize;
  // create queue
  struct queue* q = createQueue(size);
  // set the node as visited
  visited[n] = 1;
  insertQueue(q, n, size);
  // while queue is not empty...
  while(!isEmpty(q)){
    // take the node from the front of the queue
    int currentNode = dequeue(q);
    List* temp;
    // move through its adjacency list
    temp = mygraph->table[currentNode].outlist;
    while(temp != NULL) {
      int adjVertex = temp->index;
      // if not visited 
      if(visited[adjVertex] == 0){
        // mark as visited
        visited[adjVertex] = 1;
        // insert to the queue
        insertQueue(q, adjVertex, size);
      }
      // go to the next item
      temp = temp->next;
    }  
  }  
  free(q->items);
  free(q);    
}

void DFSearch(struct Graph* mygraph, int currentNode, int visited[]) {
  // get an adjacency list of the current node
  List* adjList = mygraph->table[currentNode].outlist;
  // Give it to temporary variable
  List* temp = adjList;

  // Mark current node as visited
  visited[currentNode] = 1;
  
  // while the element is not equal to null...
  while(temp!=NULL) {
    // go to the next one
    int index = temp->index;
    // check whether it was visited
    if(visited[index] == 0) {
      // if not - perform DFS on it
      DFSearch(mygraph, index, visited);
    }
    // go to the next one
    temp = temp->next;
  }       
}


int main(int argc,char *argv[])
{
  Graph mygraph;
  
  read_graph(&mygraph,argv[1]);

  // array to check whether nodes were visited or not
  int visited[mygraph.MaxSize];
  int i;
  // initialize the array
  for(i = 1; i < mygraph.MaxSize; i++){
    visited[i] = 0;
  }	
  
  // minimal out degree of the node
  int minOutDegree = mygraph.table[1].outdegree;
  int node = 1;
  // finds the minimal out degree
  for(i = 2; i < mygraph.MaxSize; i++){
    if (mygraph.table[i].outdegree < minOutDegree && mygraph.table[i].outdegree > 0){
    	minOutDegree = mygraph.table[i].outdegree;
    	node = i;
    }
  }
  printf("The node with the smallest (non-zero) out-degree is\n%d with out-degree %d\n"
  	      , node, minOutDegree);
  
  // Perform one of the searches
  if (MODE == 1){
    printf("DFS");
    DFSearch(&mygraph, node, visited);
  } else if (MODE == 2){
    printf("BFS");
    BFSearch(&mygraph, node, visited);
  }

  int max = 0;
  node = 1;
  int count = 0;
  // find the nodes
  for(i=1; i < mygraph.MaxSize; i++){
  	if (visited[i] == 1){
      if (mygraph.table[i].outdegree > max){
      	max = mygraph.table[i].outdegree;
        node = i;
      }  
      count++;
  	}
  }	
  printf("There are %d nodes reachable from the node with the\nsmallest (non-zero) out-degree and the node with the\nlargest out-degree is %d with out-degree %d\n"
  	     , count , node, max);

  freeMemory(&mygraph);
  return 0;
}  


