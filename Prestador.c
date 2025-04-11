#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prestador.h"
#include "Resultloc.h"
#include "LVO.h"
#include "Constantes.h"
#include "Costos.h"

int sonDiferentes(Prestador p1, Prestador p2)
{
    int nombre = strcmp(p1.nombre, p2.nombre);
    int servicios = strcmp(p1.servicios, p2.servicios);
    int domicilio = strcmp(p1.domicilio, p2.domicilio);
    int email = strcmp(p1.email, p2.email);
    int telefono = strcmp(p1.telefono, p2.telefono);

    if (nombre || servicios || domicilio || email || telefono)
    {

        return 1;
    }

    return 0;
}

void mostrarPrestador(Prestador p)
{

    printf("\nDNI: %d\n Nombre: %s\n Servicios: %s\n Domicilio: %s\n Email: %s\n Telefono: %s\n",
           p.dni, p.nombre, p.servicios, p.domicilio, p.email, p.telefono);
}

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls"); // comando para Windows
#else
    system("clear"); // comando para Unix
#endif
}