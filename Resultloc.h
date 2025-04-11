#ifndef RESULTLOC_H
#define RESULTLOC_H
#include "LVO.h"

typedef struct {
    int exito;
    int lugar;
} resultLoc;


typedef struct
{
    int exito;
    NodoLista *pos; // Si exito == 1 entonces retorna nodo que contiene el dni que localice
    NodoLista *pre; // Si exito == 0 retorna nodo anterior a la posicion de insercion
} resultLocLVO;


#endif