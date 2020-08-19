#include "graph.h"
/* Program that finds the node with maximum out degree,
   the node with the largest in-degree and the node
   with the smallest (non-zero) in-degree of the
   undirected graph.
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


int main(int argc,char *argv[])
{
  Graph mygraph;
  
  read_graph(&mygraph,argv[1]);
  
  /* you take it from here */
  int n[mygraph.MaxSize]; // array to count the number of indegrees
  int i;    // index
  // initialize the array
  for(i = 0; i < mygraph.MaxSize; i++){
    n[i] = 0;
  }	

  // maximal out degree of the node
  int maxOutDegree = 0;
  int node;
  // finds the maximum out degree
  for(i = 1; i < mygraph.MaxSize; i++){
    if (mygraph.table[i].outdegree > maxOutDegree){
    	maxOutDegree = mygraph.table[i].outdegree;
    	node = i;
    }
  }
  printf("Max out-degree is %d at node %s\n",maxOutDegree, mygraph.table[node].name);

  // loops through nodes in the graph
  for(i = 1; i < mygraph.MaxSize; i++){
    if (mygraph.table[i].outlist == NULL){

    }else {
      // if there is an adjacency list...
      List* current;
      current = mygraph.table[i].outlist;
      // loop through it 
      while (current != NULL){
        n[current->index]++;  // increase the in-degree for the current node
        current = current->next;
      }
    }	
  }	
  int max = 0;
  int min = n[1];

  int minNode = 1;
  // Checks for minimum and maximum in-degree
  for (i = 1; i < mygraph.MaxSize; i++){
    if(max < n[i]){
      max = n[i];
      node = i;
    }
    if(n[i] != 0 && (min > n[i] || min == 0)){
      min = n[i];
      minNode = i;
    }  
  }
  printf("Max in-degree is %d at node %s\n", max, mygraph.table[node].name);
  printf("Min in-degree is %d at node %s\n", min, mygraph.table[minNode].name);
  freeMemory(&mygraph);
  
  return(0);
  
}
