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
    NodoLista *head;
    int size;
} LVO;

void initLVO(LVO *lista);
resultLocLVO localizarLVO(LVO lista, int dni);
int altaLVO(Prestador prestador, LVO *lista);
int bajaLVO(Prestador prestador, LVO *lista);
int modificarLVO(Prestador prestador, LVO *lista);
Prestador evocarLVO(LVO lista, int dni);
void mostrarPrestador(Prestador p);
void mostrarLista(LVO lista);
void liberarLista(LVO *lista);
int memorizacionPreviaLVO(LVO *lista);

#endif