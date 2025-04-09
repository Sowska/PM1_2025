#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIBB.h"
#include "Prestador.h"
#include "Resultloc.h"

resultLoc localizarLIBB(LIBB lista, int dni) {
    resultLoc loc;
    int li = 0, ls = lista.ultimo, t;
    loc.exito = 0;

    if (lista.ultimo == -1) {  // Lista vacia
        loc.lugar = 0;
        return loc;
    }

    while (li < ls) {
        t = li + (ls - li + 1) / 2;
        if (lista.prestadores[t]->dni <= dni) {
            li = t;  // Mantiene el segmento mas grande a la derecha
        } else {
            ls = t - 1;
        }
    }
    if (lista.prestadores[li]->dni == dni) {
        loc.exito = 1;
        loc.lugar = li;
        return loc;
    }

    loc.lugar = (lista.prestadores[li]->dni < dni) ? li + 1 : li;
    return loc;
}

int altaLIBB(Prestador prestador, LIBB* lista) {
    if (lista->ultimo == MAX - 1) {
        return 2; // Lista llena
    }
    
    resultLoc aux = localizarLIBB(*lista, prestador.dni);
    if (aux.exito) {
        return 0; // El elemento ya existe
    }
    
    Prestador* newprestador = (Prestador*)malloc(sizeof(Prestador));
    if (!newprestador) {
        return 3; // Memoria insuficiente
    }
    
    *newprestador = prestador;
    lista->ultimo++;
    
    for (int i = lista->ultimo; i > aux.lugar; i--) {
        lista->prestadores[i] = lista->prestadores[i - 1];
    }
    lista->prestadores[aux.lugar] = newprestador;
    
    return 1;
}

int bajaLIBB(Prestador prestador, LIBB* lista){
if (lista->ultimo == -1) {
    return 2; // Lista vacia
}
resultLoc aux = localizarLIBB(*lista, prestador.dni);
if (!aux.exito) {
    return 0; // El elemento no existe
}
free(lista->prestadores[aux.lugar]);
for (int i = aux.lugar; i < lista->ultimo; i++) {
    lista->prestadores[i] = lista->prestadores[i + 1];
}
lista->ultimo--;
return 1; // Baja exitosa
}
int modificarLIBB(Prestador prestador, LIBB* lista) {
    if (lista->ultimo == -1) {
        return 2; // Lista vacia
    }
    
    resultLoc aux = localizarLIBB(*lista, prestador.dni);
    if (!aux.exito) {
        return 0; // El elemento no existe
    }
    
    Prestador* newprestador = (Prestador*)malloc(sizeof(Prestador));
    if (!newprestador) {
        return 3; // Memoria insuficiente
    }
    
    *newprestador = prestador;
    free(lista->prestadores[aux.lugar]);
    lista->prestadores[aux.lugar] = newprestador;
    
    return 1; // Modificacion exitosa
}
Prestador evocarLIBB(LIBB lista, int dni) {
    Prestador prestador;
    resultLoc aux = localizarLIBB(lista, dni);
    if (aux.exito) {
        prestador = *lista.prestadores[aux.lugar];
    } else {
        prestador = (Prestador){0, "", "", "", "", ""}; 
    }
    return prestador;
}

void mostrarPrestador(Prestador p) {
    printf("\nDNI: %d\n Nombre: %s\n Servicios: %s\n Domicilio: %s\n Email: %s\n Telefono: %s\n",
           p.dni, p.nombre, p.servicios, p.domicilio, p.email, p.telefono);
}

void mostrarLIBBPaginada(LIBB lista, int pagina, int elementosPorPagina) {
    if (lista.ultimo == -1) {
        printf("Lista vacia\n");
        return;
    }
    
    int inicio = (pagina - 1) * elementosPorPagina;
    int fin = inicio + elementosPorPagina <= lista.ultimo + 1 ? inicio + elementosPorPagina : lista.ultimo + 1;
    
    printf("\nPRESTADORES EN SISTEMA \n");
    for (int i = inicio; i < fin; i++) {
        printf("\nDNI: %d\n Nombre: %s\n Servicios: %s\n Domicilio: %s\n Email: %s\n Telefono: %s\n\n*---------------------*\n\n",
               lista.prestadores[i]->dni,
               lista.prestadores[i]->nombre,
               lista.prestadores[i]->servicios,
               lista.prestadores[i]->domicilio,
               lista.prestadores[i]->email,
               lista.prestadores[i]->telefono);
    }
    if (fin == lista.ultimo) {
        printf("Fin de la lista\n");
    } else {
        printf("Pagina %d de %d\n\n", pagina, (lista.ultimo / elementosPorPagina) + 1);
    }
}

void initLIBB(LIBB* lista) {
    lista->ultimo = -1;
}
void liberarLIBB(LIBB* lista) {
    for (int i = 0; i <= lista->ultimo; i++) {
        free(lista->prestadores[i]);
    }
    lista->ultimo = -1;
}