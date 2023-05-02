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
    Node *aux = copy(n); 
    int i, j ; 
    for( i = 0 ; i < 9 ; i ++ ) {
        for( j = 0 ; j < 9 ; j ++ ) {
            if( aux->sudo[i][j] == 0 ) {
                int k ; 
                for( k = 1 ; k <= 9 ; k ++ ) {
                    aux->sudo[i][j] = k ; 
                    if( is_valid(aux) ) {
                        Node *nuevo = copy(aux); 
                        pushBack(list, nuevo); 
                    }
                }
            }
        }      
    }
    return list;
}


//4.Implemente la función **int is_final(Node * n)**. 
//Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.

int is_final(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          if(n->sudo[i][j]==0)
            return 0;
    }
    return 1;
}

void deep_first_search (Node* I){
  if(I==NULL) return;
  Stack* S=createStack();
  push(S,I);
  while (size(S) != 0){
     Node* n = pop(S);
     if(n.visited==true) continue   //(n.visited==true) continue;
    
     //visitar nodo
     n.visited=true
     List* adj=get_adj_nodes(n);
     Node* aux= first(adj);
     while(aux){
        if(aux.visited==false)
          push(S,aux);
        aux=next(adj);
     }
  }
}
Node* DFS(Node* initial, int* cont){
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

/*
Construcción del grafo implícito
----

Representaremos el *proceso de resolución del problema* usando un *grafo implícito*:
- Los *nodos del grafo* corresponderán a **estados** del problema, es decir a un tablero parcialmente resuelto.
- Los *arcos* representarán las **acciones** para movernos de un estado a otro.
  
Una **acción** corresponderá a **colocar un número en una casilla vacía del tablero**.

El tipo de dato nodo contiene una matriz que representa el tablero del juego:

    typedef struct{
       int sudo[9][9];
    }Node;

Para el ejemplo de la figura la matriz, la variable sudo del nodo se vería así (los ceros indican las casillas vacías):

    5 3 0 0 7 0 0 0 0 
    6 0 0 1 9 5 0 0 0
    0 9 8 0 0 0 0 6 0
    8 0 0 0 6 0 0 0 3 
    4 0 0 8 0 3 0 0 1
    7 0 0 0 2 0 0 0 6
    0 6 0 0 0 0 2 8 0
    0 0 0 4 1 9 0 0 5
    0 0 0 0 8 0 0 7 9


*/


/*
5.Implemente la función Node* DFS(Node* n, int* cont). Esta función realiza una búsqueda en profundidad a partir del nodo n. El algoritmo es el siguiente:

1. Cree un stack S (pila) e inserte el nodo.
2. Mientras el stack S no se encuentre vacío:

   a) Saque y elimine el primer nodo de S.
   
   b) Verifique si corresponde a un estado final, si es así retorne el nodo.
   
   c) Obtenga la lista de nodos adyacentes al nodo.
   
   d) Agregue los nodos de la lista (uno por uno) al stack S.
   
   e) Libere la memoria usada por el nodo.
   
3. Si terminó de recorre el grafo sin encontrar una solución, retorne NULL.

Almacene en la variable cont, la cantidad de iteraciones que realiza el algoritmo.



void deep_first_search (node* I){
  Stack* S=createStack();
  push(S,I);
  while (size(S) != 0){
     node* n = pop(S);
     if n.visited==true continue;
    
     //visitar nodo
     n.visited=true
     List* adj=get_adj_nodes(n);
     node* aux= first(adj);
     while(aux){
        push(S,aux);
        aux=next(adj);
     }
}



*/

//Node* DFS(Node* initial, int* cont){
//  return NULL;
//}


/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/

/*

//Grafo implícito
typedef struct{
   void* data;
} Node;
List* get_adj_nodes(Node*);

*/