/*
 * C Program to Construct a Balanced Binary Search Tree
 * which has same data members as the given Doubly Linked List
 */
#include <stdio.h>
#include <stdlib.h>

struct nodo {
    struct nodo *izquierda;
    struct nodo *derecha;
    int valor;
};

void insertarNodo(struct nodo **);
struct nodo *buscarPosicionParaInsertar(int valor, struct nodo **raiz);
void inOrder(struct nodo *);


int main() {
    struct nodo *raiz = NULL;
    printf("Trabajo Practico - Arbol binario de busqueda (balanceado) \n\n");
    //TODO menu de selección de acción
    insertarNodo(&raiz);
    inOrder(raiz);

    return 0;
}


void inOrder(struct nodo *raiz)
{
    if (raiz != NULL){
        inOrder(raiz -> izquierda);
        printf("%d  ", raiz -> valor);
        inOrder(raiz -> derecha);
    }
}

void insertarNodo(struct nodo **raiz) {
    int numeroIngresado;
    int ingresaNuevoNumero;
    struct nodo *auxiliar;

    do {
        //Obtengo y creo el nodo a insertar en el árbol
        printf("Ingrese un numero: ");
        scanf("%d", &numeroIngresado);

        auxiliar = (struct nodo *)malloc(sizeof(struct nodo));
        auxiliar -> derecha = NULL;
        auxiliar -> izquierda = NULL;
        auxiliar -> valor = numeroIngresado;

        //Si no hay raíz, el nuevo nodo es la raíz. Si hay busco el lugar y lo inserto.
        if (*raiz == NULL) {
            *raiz = auxiliar;
        } else {
            int valor = auxiliar -> valor;
            printf("Intentando insertar el valor %d \n",valor);
            struct nodo *posicion = buscarPosicionParaInsertar(valor, raiz);
            if(posicion != NULL){
                printf("el valor de la posicion es: %d \n",posicion -> valor);
                if(valor > posicion -> valor){
                    printf("Se agrega a la derecha \n");
                    posicion -> derecha = auxiliar;
                } else {
                    printf("Se agrega a la izquierda \n");
                    posicion -> izquierda = auxiliar;
                }
            }
        }
        printf("Quiere ingresar un nuevo numero? \n");
        printf("1. Si \n");
        printf("0. No \n");
        scanf("%d", &ingresaNuevoNumero);
    } while (ingresaNuevoNumero != 0);
}

struct nodo *buscarPosicionParaInsertar(int valor, struct nodo **raiz) {
    struct nodo *posicion = *raiz;
    printf("El valor de la raiz es: %d \n", posicion -> valor);
    int noEncontre = 1;
    while(noEncontre == 1){
        if(valor == posicion -> valor){
            printf("El numero ya existia en el arbol.\n");
            return NULL;
        }
        while(valor > posicion -> valor){
            printf("Entre al primer while. valor: %d, valor de la posicion: %d \n", valor, posicion -> valor);
            if(posicion -> derecha != NULL){
                printf("El valor %d es mayor al del nodo %d, se busca en el nodo de la derecha\n", valor , posicion -> valor);
                posicion = posicion -> derecha;
            } else {
                printf("El valor  %d es mayor al del nodo %d y el nodo de la derecha es nulo, encontre la posicion!\n", valor , posicion -> valor);
                noEncontre = 0;
                break;
            }
        }
        while(posicion -> valor > valor){
            printf("Entre al segundo while. valor: %d, valor de la posicion: %d \n", valor, posicion -> valor);
            if(posicion -> izquierda != NULL){
                printf("El valor  %d es menor al del nodo %d, se busca en el nodo de la izquierda\n", valor , posicion -> valor);
                posicion = posicion -> izquierda;
            } else {
                printf("El valor  %d es menor al del nodo %d y el nodo de la izquierda es nulo, encontre la posicion!\n", valor , posicion -> valor);
                noEncontre = 0;
                break;
            }
        }
    }
    return posicion;
}
