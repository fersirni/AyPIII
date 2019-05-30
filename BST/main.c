#include <stdio.h>
#include <stdlib.h>

struct nodo {
    struct nodo *izquierda;
    struct nodo *derecha;
    int valor;
};

int menu(struct nodo *);

//Opcion 1
void insertarNodo(struct nodo **);
struct nodo *buscarPosicionParaInsertar(int valor, struct nodo **raiz);
//Opcion 2
void borrarNodo(struct nodo **);
//Opcion 3
struct nodo *buscarNodo(struct nodo **);
struct nodo *buscarPosicion(int valor, struct nodo **raiz);
//Opcion 4
void inOrder(struct nodo *);
//Opcion 5
void preOrder(struct nodo *);
//Opcion 6
void postOrder(struct nodo *);


int main() {
    struct nodo *raiz = NULL;
    printf("Trabajo Practico - Arbol binario de busqueda (balanceado) \n\n");
    printf("Debe cargar valores en el arbol para comenzar. \n");
    insertarNodo(&raiz);
    printf("\n Ha cargado el arbol! Que desea hacer?\n");
    int mostrarMenu = 1;
    while(mostrarMenu != 0){
        mostrarMenu = menu(raiz);
    }
    return 0;
}

int menu(struct nodo *raiz){
    int opcion;
    printf("\n\n ------------------- MENU ------------------- \n\n");
    printf("1. Cargar mas valores\n");
    printf("2. Borrar un valor\n");
    printf("3. Buscar un valor\n");
    printf("4. Imprimir en orden\n");
    printf("5. Imprimir en Pre-orden\n");
    printf("6. Imprimir en Post-orden\n");
    printf("0. Salir\n");

    scanf("%d", &opcion);
    switch (opcion){
        case 0:
            break;
        case 1:
            insertarNodo(&raiz);
            break;
        case 2:
            borrarNodo(&raiz);
            break;
        case 3:
            buscarNodo(&raiz);
            break;
        case 4:
            printf("\n Arbol recorrido en orden \n");
            inOrder(raiz);
            break;
        case 5:
            printf("\n Arbol recorrido en pre-orden \n");
            preOrder(raiz);
            break;
        case 6:
            printf("\n Arbol recorrido en post-orden \n");
            postOrder(raiz);
            break;
        default:
            printf("El valor ingresado es incorrecto. Intente nuevamente");
            break;
    }
    return opcion;
}


void inOrder(struct nodo *raiz) {
    if (raiz != NULL){
        inOrder(raiz -> izquierda);
        printf("%d  ", raiz -> valor);
        inOrder(raiz -> derecha);
    }
}

void postOrder(struct nodo *raiz) {
    if (raiz != NULL){
        postOrder(raiz -> izquierda);
        postOrder(raiz -> derecha);
        printf("%d  ", raiz -> valor);
    }
}

void preOrder(struct nodo *raiz) {
    if (raiz != NULL){
        printf("%d  ", raiz -> valor);
        preOrder(raiz -> izquierda);
        preOrder(raiz -> derecha);
    }
}

void borrarNodo(struct nodo **raiz) {
    struct nodo *posicion = buscarNodo(raiz);
    if(posicion != NULL){
        //TODO metodo de borrado.
    }
}

struct nodo *buscarNodo(struct nodo **raiz) {
    int numeroIngresado;
    printf("Ingrese el numero: ");
    scanf("%d", &numeroIngresado);
    if (*raiz == NULL) {
        printf("El arbol esta vacio");
        return NULL;
    } else {
        //printf("Intentando buscar el valor %d \n",numeroIngresado);
        struct nodo *posicion = buscarPosicion(numeroIngresado, raiz);
        if(posicion != NULL){
            printf("Valor encontrado! El valor de la posicion es: %d \n",posicion -> valor);
            return posicion;
        } else {
            printf("El valor buscado no se encuentra en el arbol. \n");
            return NULL;
        }
    }
}

struct nodo *buscarPosicion(int valor, struct nodo **raiz) {
    struct nodo *posicion = *raiz;
    //printf("El valor de la raiz es: %d \n", posicion -> valor);
    while(valor != posicion -> valor){
        if(valor > posicion -> valor){
            if(posicion -> derecha == NULL){
                return NULL;
            } else {
                posicion = posicion -> derecha;
            }
        }
        if(posicion -> valor > valor){
            if(posicion -> izquierda == NULL){
                return NULL;
            } else {
                posicion = posicion -> izquierda;
            }
        }
    }
    return posicion;
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
            //printf("Intentando insertar el valor %d \n",valor);
            struct nodo *posicion = buscarPosicionParaInsertar(valor, raiz);
            if(posicion != NULL){
                //printf("el valor de la posicion es: %d \n",posicion -> valor);
                if(valor > posicion -> valor){
                    //printf("Se agrega a la derecha \n");
                    posicion -> derecha = auxiliar;
                } else {
                    //printf("Se agrega a la izquierda \n");
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
    //printf("El valor de la raiz es: %d \n", posicion -> valor);
    int noEncontre = 1;
    while(noEncontre == 1){
        if(valor == posicion -> valor){
            printf("No se agrego. El numero ya existia en el arbol.\n");
            return NULL;
        }
        while(valor > posicion -> valor){
            //printf("Entre al primer while. valor: %d, valor de la posicion: %d \n", valor, posicion -> valor);
            if(posicion -> derecha != NULL){
                //printf("El valor %d es mayor al del nodo %d, se busca en el nodo de la derecha\n", valor , posicion -> valor);
                posicion = posicion -> derecha;
            } else {
                //printf("El valor  %d es mayor al del nodo %d y el nodo de la derecha es nulo, encontre la posicion!\n", valor , posicion -> valor);
                noEncontre = 0;
                break;
            }
        }
        while(posicion -> valor > valor){
            //printf("Entre al segundo while. valor: %d, valor de la posicion: %d \n", valor, posicion -> valor);
            if(posicion -> izquierda != NULL){
                //printf("El valor  %d es menor al del nodo %d, se busca en el nodo de la izquierda\n", valor , posicion -> valor);
                posicion = posicion -> izquierda;
            } else {
                //printf("El valor  %d es menor al del nodo %d y el nodo de la izquierda es nulo, encontre la posicion!\n", valor , posicion -> valor);
                noEncontre = 0;
                break;
            }
        }
    }
    return posicion;
}


int maximo(int a, int b){
	if (a > b){
		return a;
	}else{
		return b;
	}
}

int esHoja(struct nodo *nodo){
    if(nodo->derecha == NULL && nodo->izquierda == NULL)
        return 1;
    else
        return 0;
}


void rotacionSimple (struct nodo **nodo, int lado){
    struct nodo *aux1;
    struct nodo *aux2;
    aux1 = malloc(sizeof(struct nodo));
    aux2 = malloc(sizeof(struct nodo));
    //Rotacion Simple Izquierda
    if(lado == 1){
        aux2 = (*nodo)->derecha->izquierda;
        aux1 = (*nodo);
        (*nodo) = (*nodo)->derecha;
        (*nodo)->izquierda = aux1;
        aux1->derecha = aux2;
    }
    //Rotacion Simple Derecha
    if (lado == 0){
        aux2 = (*nodo)->izquierda->derecha;
        aux1 = (*nodo);
        (*nodo) = (*nodo)->izquierda;
        (*nodo)->derecha = aux1;
        aux1->izquierda = aux2;
    }

}


void rotacionDoble (struct nodo **nodo,int lado){
	/* rotación izquierda */
	if (lado == 1){
        rotacionSimple(&(*nodo)->izquierda, 0);
		rotacionSimple(nodo, 1);
    }
	/* rotación derecha */
    if (lado == 0){
		rotacionSimple(&(*nodo)->derecha, 1);
		rotacionSimple(nodo, 0);
    }
}


int calcularAltura(struct nodo *nodo) {
    int alturaIzquierda;
    int alturaDerecha;

    if(nodo->izquierda != NULL){
        alturaIzquierda = calcularAltura(nodo->izquierda);
    }else {
        alturaIzquierda = 0;
    }
    if(nodo->derecha != NULL){
        alturaDerecha = calcularAltura(nodo->derecha);
    }else{
        alturaDerecha = 0;
    }
    return (maximo(alturaIzquierda, alturaDerecha)) + 1;
}


void balancear(struct nodo **arbol){
    struct nodo *posicion = *arbol;
    if(*arbol != NULL){
        if (calcularAltura(posicion->izquierda) - calcularAltura(posicion->derecha) == 2){
            if (calcularAltura (posicion->izquierda->izquierda) >= calcularAltura (posicion->izquierda->derecha)){
                rotacionSimple (arbol, 1);
            }
            else{
                rotacionDoble (arbol, 1);
            }
        }else if (calcularAltura (posicion->derecha) - calcularAltura (posicion->izquierda) == 2){
            if (calcularAltura (posicion->derecha->derecha) >= calcularAltura (posicion->derecha->izquierda)){
                rotacionSimple (arbol, 0);
            }
            else{
                rotacionDoble (arbol, 0);
            }
        }
    }
}

