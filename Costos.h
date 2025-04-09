#ifndef Costos_H
#define Costos_H
#include "Constantes.h"
#include "Prestador.h"
#include "Resultloc.h"

typedef struct
{
    float total[4]; // 0.Alta - 1. Baja - 2.Evocar exitoso - 3. Evocar fallido
    float max[4];
    float med[4];
    int cant[4];
} CostosABB;

typedef struct
{
    float total[4]; // 0.Alta - 1. Baja - 2.Evocar exitoso - 3. Evocar fallido
    float max[4];
    float med[4];
    int cant[4];
} CostosLVO;

typedef struct
{
    int total[4]; // 0.Alta - 1. Baja - 2.Evocar exitoso - 3. Evocar fallido
    int max[4];
    float med[4];
    int cant[4];
} CostosLIBB;

#endif