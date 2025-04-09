#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prestador.h"
#include "Resultloc.h"
#include "LVO.h"
#include "Constantes.h"
#include "Costos.h"

void initLVO(LVO *lista)
{
    lista->head = NULL; // La lista comienza vacia
    lista->size = 0;    // Tamaño inicial es 0
}

resultLocLVO localizarLVO(LVO lista, int dni)
{
    resultLocLVO loc;
    loc.exito = 0;

    if (lista.head == NULL)
    {

        return loc;
    }

    NodoLista *actual = lista.head;
    NodoLista *anterior = NULL;

    while (actual != NULL && actual->prestador.dni < dni)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    loc.exito = actual != NULL;

    loc.lugar = index;
    if (loc.exito)
    {
        return (resultLocLVO){1, actual}; // Elemento encontrado
    }
    else
    {
        return (resultLocLVO){0, anterior}; // No encontrado, 'anterior' es donde se debe insertar
    }
}

int altaLVO(Prestador prestador, LVO *lista)
{
    if (lista->size == MAX)
    {
        return 2; // Lista llena
    }

    resultLocLVO aux = localizarLVO(*lista, prestador.dni);
    if (aux.exito)
    {
        return 0; // El elemento ya existe
    }

    NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
    if (!nuevoNodo)
    {
        return 3; // Memoria insuficiente
    }

    nuevoNodo->prestador = prestador;

    if (lista->head == NULL)
    { // Si la lista esta vacia, inserta al principio
        nuevoNodo->siguiente = lista->head;
        lista->head = nuevoNodo;
    }
    else
    { // Sino, inserta en la posicion correcta

        nuevoNodo->siguiente = aux.lugar->siguiente;
        aux.lugar->siguiente = nuevoNodo;
    }

    lista->size++;
    return 1; // Alta exitosa
}

int bajaLVO(Prestador prestador, LVO *lista)
{
    if (lista->head == NULL)
    {
        return 2; // Lista vacia
    }

    resultLoc aux = localizarLVO(*lista, prestador.dni);
    if (!aux.exito)
    {
        return 0; // El elemento no existe
    }

    NodoLista *actual = lista->head;
    NodoLista *anterior = NULL;

    while (actual != NULL && actual->prestador.dni != prestador.dni)
    {
        anterior = actual;
        actual = actual->siguiente;
    }

    if (anterior == NULL)
    { // El nodo a eliminar es el primero
        lista->head = actual->siguiente;
    }
    else
    {
        anterior->siguiente = actual->siguiente;
    }

    free(actual);
    lista->size--;
    return 1; // Baja exitosa
}
int modificarLVO(Prestador prestador, LVO *lista)
{
    if (lista->head == NULL)
    {
        return 2; // Lista vacia
    }

    resultLoc aux = localizarLVO(*lista, prestador.dni);
    if (!aux.exito)
    {
        return 0; // El elemento no existe
    }

    NodoLista *actual = lista->head;
    int index = 0;

    while (actual != NULL && index < aux.lugar)
    {
        actual = actual->siguiente;
        index++;
    }

    if (actual != NULL)
    {
        actual->prestador = prestador;
        return 1;
    }

    return 0;
}
Prestador evocarLVO(LVO lista, int dni)
{
    Prestador prestador;
    resultLoc aux = localizarLVO(lista, dni);
    if (aux.exito)
    {
        prestador = lista.head->prestador;
    }
    else
    {
        prestador = (Prestador){0, "", "", "", "", ""};
    }
    return prestador;
}
void mostrarPrestador(Prestador p)
{
    printf("\nDNI: %d\n Nombre: %s\n Servicios: %s\n Domicilio: %s\n Email: %s\n Telefono: %s\n",
           p.dni, p.nombre, p.servicios, p.domicilio, p.email, p.telefono);
}
void mostrarLista(LVO lista)
{
    NodoLista *actual = lista.head;
    while (actual != NULL)
    {
        mostrarPrestador(actual->prestador);
        actual = actual->siguiente;
    }
}
void liberarLista(LVO *lista)
{
    NodoLista *actual = lista->head;
    while (actual != NULL)
    {
        NodoLista *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    lista->head = NULL;
    lista->size = 0;
}
int memorizacionPreviaLVO(LVO *lista)
{


}