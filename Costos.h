#ifndef COSTOS_H
#define COSTOS_H

#include <stdio.h>
#include "Constantes.h"
#include "Prestador.h"
#include "Resultloc.h"

// Esta estructura ahora registra máximos, totales y cantidades
typedef struct {
    float maxAlta;
    float totalAlta;
    int cantAlta;
    float medAlta;

    float maxBaja;
    float totalBaja;
    int cantBaja;
    float medBaja;

    float maxEvocacionExitosa;
    float totalEvocacionExitosa;
    int cantEvocacionExitosa;
    float medEvocacionExitosa;

    float maxEvocacionFallida;
    float totalEvocacionFallida;
    int cantEvocacionFallida;
    float medEvocacionFallida;
} CostosEstructura;

// Costos globales por estructura
typedef struct {
    CostosEstructura lvo;
    CostosEstructura libb;
    CostosEstructura abb;
} CostosGlobales;

void mostrarCostos(const char* nombre, CostosEstructura c) {
    printf("\n--------%s--------\n", nombre);

    printf("Máximo de alta exitosa: %.2f\n", c.maxAlta);
    printf("Promedio de alta exitosa: %.2f\n\n", c.medAlta);
   //printf("Total de alta exitosa: %.2f\n\n", c.totalAlta);
    //printf("Cantidad de altas exitosas: %d\n\n", c.cantAlta);

    printf("Máximo de baja exitosa: %.2f\n", c.maxBaja);
    printf("Promedio de baja exitosa: %.2f\n\n", c.medBaja);
    //printf("Total de baja exitosa: %.2f\n\n", c.totalBaja);

    printf("Máximo de evocación exitosa: %.2f\n", c.maxEvocacionExitosa);
    printf("Promedio de evocación exitosa: %.2f\n\n", c.medEvocacionExitosa);
    //printf("Total de evocación exitosa: %.2f\n\n", c.totalEvocacionExitosa);

    printf("Máximo de evocación NO exitosa: %.2f\n", c.maxEvocacionFallida);
    printf("Promedio de evocación NO exitosa: %.2f\n\n", c.medEvocacionFallida);
    //printf("Total de evocación NO exitosa: %.2f\n\n", c.totalEvocacionFallida);
}

void mostrarCostosGlobales(CostosGlobales costos) {
    mostrarCostos("LVO", costos.lvo);
    mostrarCostos("LIBB", costos.libb);
    mostrarCostos("ABB", costos.abb);
}
void inicializarCostos(CostosGlobales *costosGlobales) {
    costosGlobales->abb.maxAlta = 0;
    costosGlobales->abb.totalAlta = 0;
    costosGlobales->abb.cantAlta = 0;
    costosGlobales->abb.medAlta = 0;

    costosGlobales->abb.maxBaja = 0;
    costosGlobales->abb.totalBaja = 0;
    costosGlobales->abb.cantBaja = 0;
    costosGlobales->abb.medBaja = 0;

    costosGlobales->abb.maxEvocacionExitosa = 0;
    costosGlobales->abb.totalEvocacionExitosa = 0;
    costosGlobales->abb.cantEvocacionExitosa = 0;
    costosGlobales->abb.medEvocacionExitosa = 0;

    costosGlobales->abb.maxEvocacionFallida = 0;
    costosGlobales->abb.totalEvocacionFallida = 0;
    costosGlobales->abb.cantEvocacionFallida = 0;
    costosGlobales->abb.medEvocacionFallida = 0;

    // Inicializar LIBB
    costosGlobales->libb.maxAlta = 0;
    costosGlobales->libb.totalAlta = 0;
    costosGlobales->libb.cantAlta = 0;
    costosGlobales->libb.medAlta = 0;

    // Inicializar LVO
    costosGlobales->lvo.maxAlta = 0;
    costosGlobales->lvo.totalAlta = 0;
    costosGlobales->lvo.cantAlta = 0;
    costosGlobales->lvo.medAlta = 0;
}

void calculoPromediosCostos(CostosGlobales *costosGlobales){
    // Cálculo de promedios para ABB
    if (costosGlobales->abb.cantAlta > 0)
    //Medio alta
        costosGlobales->abb.medAlta = costosGlobales->abb.totalAlta / costosGlobales->abb.cantAlta;
    if (costosGlobales->abb.cantBaja > 0)
        //Medio baja
        costosGlobales->abb.medBaja = costosGlobales->abb.totalBaja / costosGlobales->abb.cantBaja;
    if (costosGlobales->abb.cantEvocacionExitosa > 0)
        //Medio evocacion exitosa
        costosGlobales->abb.medEvocacionExitosa = costosGlobales->abb.totalEvocacionExitosa / costosGlobales->abb.cantEvocacionExitosa;
    if (costosGlobales->abb.cantEvocacionFallida > 0)
        //Medio evocacion fallida
        costosGlobales->abb.medEvocacionFallida = costosGlobales->abb.totalEvocacionFallida / costosGlobales->abb.cantEvocacionFallida;
    
    // Cálculo de promedios para LIBB
    if (costosGlobales->libb.cantAlta > 0)
    //Medio alta
        costosGlobales->libb.medAlta = costosGlobales->libb.totalAlta / costosGlobales->libb.cantAlta;
    if (costosGlobales->libb.cantBaja > 0) 
        //Medio baja
        costosGlobales->libb.medBaja = costosGlobales->libb.totalBaja / costosGlobales->libb.cantBaja;
    if (costosGlobales->libb.cantEvocacionExitosa > 0)  
        //Medio evocacion exitosa
        costosGlobales->libb.medEvocacionExitosa = costosGlobales->libb.totalEvocacionExitosa / costosGlobales->libb.cantEvocacionExitosa;
    if (costosGlobales->libb.cantEvocacionFallida > 0)  
        //Medio evocacion fallida
        costosGlobales->libb.medEvocacionFallida = costosGlobales->libb.totalEvocacionFallida / costosGlobales->libb.cantEvocacionFallida;

    // Cálculo de promedios para LVO
    if (costosGlobales->lvo.cantAlta > 0)
        //Medio alta
        costosGlobales->lvo.medAlta = costosGlobales->lvo.totalAlta / costosGlobales->lvo.cantAlta;
    if (costosGlobales->lvo.cantBaja > 0)   
        //Medio baja
        costosGlobales->lvo.medBaja = costosGlobales->lvo.totalBaja / costosGlobales->lvo.cantBaja;
    if (costosGlobales->lvo.cantEvocacionExitosa > 0)
        //Medio evocacion exitosa
        costosGlobales->lvo.medEvocacionExitosa = costosGlobales->lvo.totalEvocacionExitosa / costosGlobales->lvo.cantEvocacionExitosa;
    if (costosGlobales->lvo.cantEvocacionFallida > 0)
        //Medio evocacion fallida
        costosGlobales->lvo.medEvocacionFallida = costosGlobales->lvo.totalEvocacionFallida / costosGlobales->lvo.cantEvocacionFallida;      

}



#endif
