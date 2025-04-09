#include <stdlib.h>
#include "ABB.h"
#include "Prestador.h"
#include "Constantes.h"

NodoArbol *crearNodo(Prestador prestador)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if(nuevo != NULL)
    {
        nuevo->prestador = prestador;
        nuevo->izq = NULL;
        nuevo->der = NULL;
    }

    return nuevo;
}

void freeNodo(NodoArbol *nodo)
{
    if (nodo == NULL)
    {
        return;
    }
    freeNodo(nodo->izq);

    freeNodo(nodo->der);

    free(nodo);
}

void vaciarArbol(Arbol *arbol)
{
    if (arbol->raiz != NULL)
    {
        freeNodo(arbol->raiz);
        arbol->raiz = NULL;
    }
}

// localizar

int localizarABB(Arbol *arbol, int dni, float *costo)
{
    *costo = 0;

    if (arbol->raiz == NULL)
    {

        return 0;
    }

    arbol->pos = arbol->raiz;
    arbol->padre = arbol->raiz;

    while (arbol->pos != NULL && dni != arbol->pos->prestador.dni)
    {
        *costo = *costo + 1;

        if (arbol->pos->prestador.dni < dni)
        {
            arbol->padre = arbol->pos;
            arbol->pos = arbol->pos->der;
        }
        else
        {
            arbol->padre = arbol->pos;
            arbol->pos = arbol->pos->izq;
        }
        *costo = *costo + 1;
    }

    if (arbol->pos != NULL)
    {
        *costo = *costo + 1;
    }
    return (arbol->pos != NULL);
}

int altaABB(Arbol *arbol, Prestador x, float *costo, int cant)
{

    float auxCosto = 0.0;

    if (localizarABB(arbol, x.dni, costo))
    {
        *costo = auxCosto;
        return 0;
    }
    else
    {
        NodoArbol *nuevoNodo = crearNodo(x);
        if (arbol->raiz == NULL)
        {
            arbol->raiz = nuevoNodo;
            arbol->padre = nuevoNodo;
            auxCosto = auxCosto + 0.5;
        }
        else
        {
            if (x.dni > arbol->padre->prestador.dni)
            {
                arbol->padre->der = nuevoNodo;
            }
            else
            {
                arbol->padre->izq = nuevoNodo;
            }
            auxCosto = auxCosto + 0.5;
        }
        *costo = auxCosto;
        return 1;
    }
}

    int bajaABB(Arbol *arbol, Prestador x, float *costo){
    NodoArbol *auxi, *elem;
    float auxCosto = 0.0;

    if (arbol->raiz == NULL)
    {
        *costo = auxCosto;
        return 0;
    }

    if (localizarABB(arbol, x.dni, costo))
    {
        if (sonDiferentes(arbol->pos->prestador, x))
        {
            return 0;
        }

        // Caso 1: Nodo hoja - sin hijos
        if (arbol->pos->der == NULL && arbol->pos->izq == NULL)
        {
            if (arbol->pos == arbol->raiz)
            {
                arbol->raiz = NULL;
                auxCosto += 0.5;
                free(arbol->pos);
                arbol->pos = NULL;
            }
            else
            {
                if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
                {
                    arbol->padre->izq = NULL;
                }
                else
                {
                    arbol->padre->der = NULL;
                }
                auxCosto += 0.5;
                free(arbol->pos);
                arbol->pos = NULL;
            }
        }
        // Caso 2: Nodo con un solo hijo
        else if (arbol->pos->der == NULL || arbol->pos->izq == NULL)
        {
            auxi = (arbol->pos->izq != NULL) ? arbol->pos->izq : arbol->pos->der;
            if (arbol->pos == arbol->raiz)
            {
                arbol->raiz = auxi;
            }
            else
            {
                if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
                {
                    arbol->padre->izq = auxi;
                }
                else
                {
                    arbol->padre->der = auxi;
                }
                auxCosto += 0.5;
            }
            free(arbol->pos);
            arbol->pos = NULL;
        }
        // Caso 3: Nodo con dos hijos
        else
        {
            elem =  arbol->pos->der;  
            arbol->padre = arbol->pos;
            NodoArbol *ant_aux = NULL;

            while (elem->izq != NULL) //Esto busca el minimo del subarbol derecho (nueva politica de reemplazo).
            {
                ant_aux = elem;
                elem = elem->izq;
            }
            arbol->pos->prestador = elem->prestador;
            auxCosto += 1.0;

            if (ant_aux == NULL)
            {

        // El hijo derecho es el minimo entonces
        arbol->pos->der = elem->der;
            }
            else
            {
        // El minimo tiene hijo derecho
        ant_aux->izq = elem->der;
            }

            auxCosto += 0.5;
            free(elem);
            elem = NULL;
        }

        *costo = auxCosto;
        return 1;
    }
    *costo = auxCosto;
    return 0;
}

Prestador evocarABB(Arbol *arbol, int x, int *exito, float *costo)
{
    float auxCosto = 0.0;
    Prestador p;

    int result = localizarABB(arbol, x, &auxCosto);

    if (result)
    {
        *exito = 1;
        p = arbol->pos->prestador;
    }
    else
    {
        *exito = 0;
    }

    *costo = auxCosto;
    return p;
}

void mostrarEstructuraABB(NodoArbol *raiz)
{
    if (raiz == NULL)
    {
        return;
    }

    NodoArbol *stack[MAX];
    int top = -1;
    stack[++top] = raiz;
    int contador = 0;

    while (top >= 0)
    {
        NodoArbol *actual = stack[top--];

        imprimirPrestador(actual->prestador);

        if (actual->izq != NULL)
        {
            printf("DNI del nodo izquierdo: %d\n", actual->izq->prestador.dni);
        }
        else
        {
            printf("Nodo izquierdo: NULL\n");
        }

        if (actual->der != NULL)
        {
            printf("DNI del nodo derecho: %d\n", actual->der->prestador.dni);
        }
        else
        {
            printf("Nodo derecho: NULL\n");
        }

        printf("\n\t*-*-*-*-*-**-*-*-*-*-*\n");

        contador++;

        if (contador % 10 == 0)
        {
            printf("Presiona Enter para continuar...\n");
            getchar();
            limpiarPantalla();
        }

        if (actual->der != NULL)
        {
            stack[++top] = actual->der;
        }

        if (actual->izq != NULL)
        {
            stack[++top] = actual->izq;
        }
    }

    printf("\n** FIN DE LA LISTA **\n");
}

void initArbol(Arbol *arbol)
{
    arbol->raiz = NULL;
    arbol->pos = NULL;
    arbol->padre = NULL;
}