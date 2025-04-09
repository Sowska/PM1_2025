#ifndef LIBB_H
#define LIBB_H
#include "Prestador.h"
#include "Resultloc.h"


#define MAX 10
#define MINDNI 10000000
#define INFINITO 99999999

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
void initLIBB(LIBB* lista);
void liberarLIBB(LIBB* lista);

#endif // LIBB_H