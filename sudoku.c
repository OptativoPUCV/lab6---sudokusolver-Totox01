#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int marca[10];
  for (int i = 0; i < 9; i++){
    for (int k = 0; k < 10; k++){
      marca[k] = 0;
    }
    for(int j = 0; j < 9; j++){
      int num = n->sudo[i][j];
      if(num != 0){
        if(marca[num] == 1) return 0;
        marca[num] = 1;
      }
    }
  }
  for(int j = 0; j < 9; j++){
    for(int k = 0; k < 10; k++){
      marca[k] = 0;
    }
    for(int i = 0; i < 9; i++){
      int num = n->sudo[i][j];
      if(num != 0){
        if(marca[num] == 1) return 0;
      }
      marca[num] = 1;
    }
  }
  for(int k = 0; k < 9; k++){
    for(int p = 0; p < 10; p++){
      marca[p] = 0;
    }
    for(int p = 0; p < 9; p++){
      int i = 3*(k/3) + (p/3);
      int j = 3*(k%3) + (p%3);
      int num = n->sudo[i][j];
      if(num != 0){
        if(marca[num] == 1) return 0;
        marca[num] = 1;
      }
    }
  }
    return 1;
}


List* get_adj_nodes(Node* n){
   List* list=createList();
   int row = -1;
   int col = -1;
   for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
         if(n->sudo[i][j] == 0){
            row = i;
            col = j;
            break;
         }
      }
      if(row != -1) break;
   }
   if(row == -1) return list;

   for(int k = 1; k <= 9; k++){
      Node* adj = copy(n);
      adj->sudo[row][col] = k;
      if (is_valid(adj) == 1){
        pushBack(list, adj);
      } else {
        free(adj);
      }
   }
   return list;
}



int is_final(Node* n){
  for (int i = 0; i < 9; i++){
    for (int j = 0; j < 9; j++){
      if (n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* pila = createStack();
  push(pila, initial);
  *cont = 0;
  while(is_empty(pila) == 0){
    (*cont)++;
    Node* current = top(pila);
    pop(pila);
    if(is_final(current) == 1){
      return current;
    }
    List* adj = get_adj_nodes(current);
    Node* aux = first(adj);
    while (aux != NULL){
      push(pila, aux);
      aux = next(adj);
    } 
    free(current);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/