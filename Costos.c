#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIBB.h"
#include "Prestador.h"
#include "Resultloc.h"
#include "Costos.h"


void mostrarCostosLIBB(CostosLIBB costos)
{
    printf("\n--------LIBB--------\n");

    printf("maximo de alta exitosa: %f\n", costos.max[0]);
    printf("medio de alta exitosa: %.2f\n\n", costos.med[0]);

    printf("maximo de baja exitosa: %f\n", costos.max[1]);
     printf("medio de baja exitosa: %.2f\n\n", costos.med[1]);

    printf("maximo de evocacion exitosa: %f\n", costos.max[2]);
     printf("medio de evocacion exitosa: %.2f\n\n", costos.med[2]);

    printf("maximo de evocacion NO exitosa: %f\n", costos.max[3]);
    printf("medio de evocaciones NO exitosa: %.2f\n\n\n", costos.med[3]);


}

void mostrarCostosLVO(CostosLVO costos)
{
    printf("\n--------LVO--------\n");

    printf("maximo de alta exitosa: %f\n", costos.max[0]);
    printf("medio de alta exitosa: %.2f\n\n", costos.med[0]);

    printf("maximo de baja exitosa: %f\n", costos.max[1]);
     printf("medio de baja exitosa: %.2f\n\n", costos.med[1]);

    printf("maximo de evocacion exitosa: %f\n", costos.max[2]);
     printf("medio de evocacion exitosa: %.2f\n\n", costos.med[2]);

    printf("maximo de evocacion NO exitosa: %f\n", costos.max[3]);
    printf("medio de evocacion NO exitosa: %.2f\n\n\n", costos.med[3]);

}

void mostrarCostosABB(CostosABB costos)
{
    printf("\n--------ABB--------\n");

    printf("maximo de alta exitosa: %.1f\n", costos.max[0]);
    printf("medio de alta exitosa: %.2f\n\n", costos.med[0]);

    printf("maximo de baja exitosa: %.1f\n", costos.max[1]);
     printf("medio de baja exitosa: %.2f\n\n", costos.med[1]);

    printf("maximo de evocacion exitosa: %.1f\n", costos.max[2]);
     printf("medio de evocacion exitosa: %.2f\n\n", costos.med[2]);

    printf("maximo de evocacion NO exitosa: %.1f\n", costos.max[3]);
    printf("medio de evocacion NO exitosa: %.2f\n\n\n", costos.med[3]);
}