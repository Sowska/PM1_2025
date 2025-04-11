#ifndef LVO_H
#define LVO_H
#include "Prestador.h"
#include "Resultloc.h"
#include "Constantes.h"



typedef struct NodoLista
{
    Prestador prestador;
    struct NodoLista *siguiente;
} NodoLista;

typedef struct
{
    int exito;
    NodoLista *pos; // Si exito == 1 entonces retorna nodo que contiene el dni que localice
    NodoLista *pre; // Si exito == 0 retorna nodo anterior a la posicion de insercion
} resultLocLVO;

typedef struct
{
    NodoLista *head;
    int size;
} LVO;

void inicializarLista(LVO *lista);
resultLocLVO localizarLVO(LVO lista, int dni, int *costo);
int altaLVOMem(Prestador prestador, LVO *lista);
int altaLVO(Prestador prestador, LVO *lista, float *costo);
int bajaLVOConfirmada(int dni, LVO *lista);
int bajaLVOAutomatica(Prestador prestador, LVO *lista, float *costo);
void modificarLVO(int dni, LVO *lista);
Prestador evocarLVO(LVO lista, int dni, int *costo);
void mostrarLista(LVO lista);
void liberarLista(LVO *lista);
int memorizacionPrevia(LVO *lista);


#endif