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

int recorrer_ileras(Node* n,int i, int j){
  int k;
  for(k = 0 ; k < 9 ; k++){
    if(n->sudo[i][k] == n->sudo[i][j] && k != j && n->sudo[i][k] != 0) return 1;
  }
  for(k = 0 ; k < 9 ; k++){
    if(n->sudo[k][j] == n->sudo[i][j] && k != i && n->sudo[k][j] != 0) return 1;
  }
  return 0;
}

int recorrer_sub(Node* n,int i,int j){
  int m,h;
  int aux[10] = {};

  //guardar numeros en arreglo
  for(m = 0; m < 3 ; m++){
    for(h = 0 ; h < 3 ; h++){
      aux[(n->sudo[m+3*i][h+3*j])]++;
    }
  }
  for(m = 1 ; m < 10 ; m++){
    if(aux[m] > 1) return 1;
  }
  return 0;
}

int is_valid(Node* n){
  int i,j;
  //submatriz
  for(i = 0 ; i < 3 ; i++){
    for(j = 0 ; j < 3 ; j++){
      if(recorrer_sub(n,i,j)==1){
        return 0;
      }
    }
  }

  //ileras
  for(i = 0 ; i < 9 ; i++){
    for(j = 0 ; j < 9 ;j++){
      if(recorrer_ileras(n,i,j) == 1) return 0;
    }
  }

    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,k;
    for(i = 0;i < 9;i++){
      for(j = 0;j < 9;j++){
        if(n->sudo[i][j]==0){
          for(k = 1;k < 10;k++){
            n->sudo[i][j] = k;
            if(is_valid(n)){
              Node*adj=copy(n);
              pushBack(list,adj);
            }
          }
          n->sudo[i][j]=0;
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  int i,j;
  for(i = 0 ; i < 9 ; i++){
    for(j = 0 ; j < 9 ; j++){
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *pila = createStack();
  push(pila,initial);
  while(get_size(pila) != 0){
    Node *n = top(pila);
    pop(pila);
    if(is_final(n) == 1) return n;

    //visita
    List *adj = get_adj_nodes(n);
    Node *aux = first(adj);
    while(aux != NULL){
      push(pila,aux);
      aux = next(adj);
    }
    free(n);
    (*cont)++;
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
}
*/