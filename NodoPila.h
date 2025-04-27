#ifndef PILA_H
#define PILA_H

#include <stdio.h>  // Para printf
#include <stdlib.h> // Para malloc, free, exit

typedef struct NodoArbol
{
    Prestador prestador;
    struct NodoArbol *izq;
    struct NodoArbol *der;
} NodoArbol;

typedef struct NodoPila
{
    NodoArbol *dato;
    struct NodoPila *sig;
} NodoPila;

void push(NodoPila **pila, NodoArbol *nodo)
{
    NodoPila *nuevo = (NodoPila *)malloc(sizeof(NodoPila));
    if (!nuevo) {
        printf("Error de memoria\n");
        exit(1);
    }
    nuevo->dato = nodo;
    nuevo->sig = *pila;
    *pila = nuevo;
}

NodoArbol *pop(NodoPila **pila)
{
    if (*pila == NULL)
        return NULL;
    NodoPila *aux = *pila;
    NodoArbol *dato = aux->dato;
    *pila = aux->sig;
    free(aux);
    return dato;
}

int pilaVacia(NodoPila *pila)
{
    return pila == NULL;
}


#endif
