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


void deep_first_search (Node* I){
  if(I==NULL) return;
  Stack* S=createStack();
  push(S,I);
  while (size(S) != 0){
     Node* n = top(S);
     if(n->visited==true) continue;
    
     //visitar nodo
     n->visited=true;
     List* adj=get_adj_nodes(n);
     Node* aux= first(adj);
     while(aux){
        if(aux->visited==false)
          push(S,aux);
        aux=next(adj);
     }
  }
}



Node* DFS(Node* initial, int* cont){
  return NULL;
}
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

Ejercicios
--

1.Cree una función que a partir de un nodo genere una **lista con los nodos adyacentes**:

    List* get_adj_nodes(Node* n){
       List* list=createList();
       
       //obtenga los nodos adyacentes a n
       //y agréguelos a la lista
       
       return list;
    }
    

Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.

> - Para el caso del ejemplo, la función debería retornar una lista con **9 nodos**. Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
> - Utilice la función Node* copy(Node* n) para copiar nodos.

    */

// 1.Cree una función que a partir de un nodo genere una **lista con los nodos adyacentes**:



//Recuerde que los nodos adyacentes son generados aplicando las acciones al estado actual.

//> - Para el caso del ejemplo, la función debería retornar una lista con **9 nodos**. Cada uno de ellos idéntico al nodo original pero cambiando el valor de la primera casilla vacía, es decir: sudo[0][2], por 1, 2, ..., 9.
//> - Utilice la función Node* copy(Node* n) para copiar nodos.

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
                    Node *nuevo = copy(aux); 
                    pushBack(list, nuevo); 
                }
            }
        }      
    }
    return list;
}




/*
2.Cree la función **int is_valid(Node * n)**, para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

- No se repitan números en las filas
- No se repitan números en las columnas
- No se repitan números en las submatrices de 3x3

Si el estado es válido la función retorna 1, si no lo es retorna 0.

> Para marcar los números que vayan apareciendo en una fila/columna/submatriz puede usar un arreglo de enteros de largo 10 inicializado con 0s. Cada vez que aparezca un número i, verifique que la casilla i del arreglo sea igual a 0, luego márquela con un '1'. Si la casilla es '1' quiere decir que el número ya estaba marcado por lo que la fla/columna/submatriz no es válida.

----
**¿Cómo recorrer las submatrices de 3x3?**
El siguiente código se puede usar para recorrer los elementos de una sumbatriz k (por ejemplo k=4):

    int k=4,p; 
    for(p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        printf("%d ",nodo->sudo[i][j]);
        if(p%3 == 2) printf("\n");
    }

La salida del código con el estado de la figura es (submatriz del centro):
    
    0 6 0
    8 0 3
    0 2 0

-----

*/

//2.Cree la función **int is_valid(Node * n)**, para validar si un estado/nodo es válido (cumple con las restricciones del problema). Debe validar que:

//- No se repitan números en las filas
//- No se repitan números en las columnas
//- No se repitan números en las submatrices de 3x3

int is_valid(Node * n){
    int i, j, k ; 
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
                if( filas[i][num] == 1 ) return 0 ; 
                if( columnas[j][num] == 1 ) return 0 ; 
                int k = 3*(i/3) + (j/3) ; 
                if( submatriz[k][num] == 1 ) return 0 ; 
                filas[i][num] = 1 ; 
                columnas[j][num] = 1 ; 
                submatriz[k][num] = 1 ; 
            }
        }
    }
    return 1 ;
}



/*
3.Modifique la función *get_adj_nodes* para que sólo los nodos válidos sean retornados (use la función *is_valid*).

*/


//3.Modifique la función *get_adj_nodes* para que sólo los nodos válidos sean retornados (use la función *is_valid*).


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








/*

4.Implemente la función **int is_final(Node * n)**. Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.

Ya está listo el grafo implícito, ahora necesitamos construir un método de búsqueda que a partir del estado inicial sea capaz de explorar el grafo de manera sistemática hasta alcanzar un nodo final.

Implementando una búsqueda en profundidad

*/

// Esta función retorna 1 si el nodo corresponde a un nodo final (es decir, todos los valores de la matriz son distintos a 0) y 0 en caso contrario.

int is_final(Node * n){
  
}












/*

Implementando una búsqueda en profundidad
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

/*
int main( int argc, char *argv[] ){
  Node* initial= read_file("s12a.txt");;
  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);
  return 0;
}*/
<<<<<<< HEAD
=======

/*

//Grafo implícito
typedef struct{
   void* data;
} Node;
List* get_adj_nodes(Node*);

*/
>>>>>>> a5b4d5bf292a729fd510d420d79e6d0fb9a3b5ae
