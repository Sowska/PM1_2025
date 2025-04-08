#ifndef LIBB_H
#define LIBB_H
#define MAX 10
#include "Prestador.h"
typedef struct {
    Prestador* prestadores[MAX];
    int ultimo;
} LIBB;

resultLoc localizarLIBB(LIBB lista, int dni);
int altaLIBB(Prestador prestador, LIBB* lista);
int bajaLIBB(Prestador prestador, LIBB* lista);
int modificarLIBB(Prestador prestador, LIBB* lista);
Prestador evocarLIBB(LIBB lista, int dni);
void mostrarPrestador(Prestador p);
void mostrarLIBBPaginada(LIBB lista, int pagina, int elementosPorPagina);

#endif // LIBB_H