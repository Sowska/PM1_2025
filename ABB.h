#ifndef ABB_H
#define ABB_H
#include "Prestador.h"

typedef struct NodoArbol
{
    Prestador prestador;
    struct NodoArbol *izq;
    struct NodoArbol *der;
} NodoArbol;

typedef struct{
    NodoArbol *raiz;
    NodoArbol *pos;
    NodoArbol *padre;
} Arbol;

NodoArbol *crearNodo(Prestador prestador);
void freeNodo(NodoArbol *nodo);
void vaciarArbol(Arbol *arbol);
int localizarABB(Arbol *arbol, int dni, float *costo);
int altaABB(Arbol *arbol, Prestador x, float *costo, int cant);
int bajaABB(Arbol *arbol, Prestador x, float *costo);
Prestador evocarABB(Arbol *arbol, int x, int *exito, float *costo);
void mostrarEstructuraABB(NodoArbol *raiz);
void initArbol(Arbol *arbol);


#endif