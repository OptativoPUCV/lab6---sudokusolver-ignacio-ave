#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
   bool visited;
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  int i,j;
  for(i=0;i<9;i++)
     for(j=0;j<9;j++)
        n->sudo[i][j]=0;
  n->visited=false;

  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    int i,j;
    for(i=0;i<9;i++)
       for(j=0;j<9;j++)
          new->sudo[i][j]=n->sudo[i][j];
    new->visited=n->visited;
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

int is_valid(Node * n){
    int i, j; 
    int filas[9][10] ; 
    int columnas[9][10] ; 
    int submatriz[9][10] ; 
    for( i = 0 ; i < 9 ; i ++ ) {
        for( j = 0 ; j < 10 ; j ++ ) {
            filas[i][j] = 0 ; 
            columnas[i][j] = 0 ; 
            submatriz[i][j] = 0 ; 
        }
    }
    for( i = 0 ; i < 9 ; i ++ ) {
        for( j = 0 ; j < 9 ; j ++ ) {
            int num = n->sudo[i][j] ; 
            if( num != 0 ) {
                if( filas[i][num] == 1 ) {
                    return 0 ; 
                }
                else {
                    filas[i][num] = 1 ; 
                }
                if( columnas[j][num] == 1 ) {
                    return 0 ; 
                }
                else {
                    columnas[j][num] = 1 ; 
                }
                int k = 3*(i/3) + (j/3) ; 
                if( submatriz[k][num] == 1 ) {
                    return 0 ; 
                }
                else {
                    submatriz[k][num] = 1 ; 
                }
            }
        }
    }
    return 1 ;

}

List* get_adj_nodes(Node * n ) {
    List *list = createList(); 
    int i, j ; 
    for( i = 0 ; i < 9 ; i ++ ) {
        for( j = 0 ; j < 9 ; j ++ ) {
            if( n->sudo[i][j] == 0 ) {
                int k ; 
                for( k = 1 ; k <= 9 ; k ++ ) {
                    Node *aux = copy(n);
                    aux->sudo[i][j] = k ; 
                    if( is_valid(aux) ) {
                        pushBack(list, aux); 
                    } else {
                        free(aux);
                    }
                }
                return list;
            }
        }      
    }
    return list;
}



int is_final(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          if(n->sudo[i][j]==0)
            return 0;
    }
    return 1;
}

int size(List* l){
  int cont=0;
  Node* aux= first(l);
  while(aux){
    cont++;
    aux=next(l);
  }
  return cont;
}






Node* DFS(Node* initial, int* cont) {
    if (initial == NULL) return NULL;
    Stack* S = createStack();
    push(S, initial);
    *cont = 0;

    while (size(S) != 0) {
        Node* n = top(S);
        pop(S);

        if (n->visited == true) {
            free(n);
            continue;
        }

        n->visited = true;
        (*cont)++;

        if (is_final(n)) {
            clean(S); // libera la memoria del stack sin liberar los nodos
            return n;
        }

        List* adj = get_adj_nodes(n);
        Node* aux = first(adj);

        if (!aux) { // No hay nodos adyacentes válidos
            free(n);
            continue;
        }

        while (aux) {
            if (aux->visited == false)
                push(S, aux);
            aux = next(adj);
        }

        free(n); // Libera la memoria del nodo que ya no se necesita
        clean(adj); // Libera la memoria de la lista de nodos adyacentes sin liberar los nodos
    }

    return NULL;
}
/*
void deep_first_search(Node* I){
  if(I == NULL) return;
  Stack* S = createStack();
  push(S, I);
  while (size(S) != 0){
     Node* n = top(S);
     if(n->visited == true) {
        pop(S); 
        continue;
     }

     //visitar nodo
     n->visited = true;
     List* adj = get_adj_nodes(n);
     Node* aux = first(adj);
     while(aux){
        if(aux->visited == false)
          push(S, aux);
        aux = next(adj);
     }
  }
}
*/

/*


int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}

*/
