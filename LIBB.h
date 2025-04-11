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

resultLoc localizarLIBB(LIBB lista, int dni, int *costo);
int altaLIBB(Prestador prestador, LIBB *lista, float *costo);
int bajaLIBBAutomatica(int dni, LIBB *lista, float *costo);
int modificarLIBB(int dni, LIBB *lista);
Prestador evocarLIBB(LIBB lista, int dni, int *costo);
int bajaLIBBConfirmada(int dni, LIBB *lista, float *costo);
void mostrarLIBBPaginada(LIBB lista, int pagina, int elementosPorPagina);
void initLIBB(LIBB* lista);
void liberarLIBB(LIBB* lista);
int memorizacionPreviaLIBB(LIBB* lista);

#endif // LIBB_H