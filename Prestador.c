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

void modificar_nombre(Prestador* p) {
    char nuevo_nombre[50];
    printf("Ingrese el nuevo nombre: ");
    fflush(stdin);
    fgets(nuevo_nombre, sizeof(nuevo_nombre), stdin);
    nuevo_nombre[strcspn(nuevo_nombre, "\n")] = '\0'; // Eliminar salto de línea
    strcpy(p->nombre, nuevo_nombre);
}

void modificar_servicio(Prestador* p) {
    char nuevo_servicio[100];
    printf("Ingrese el/los nuevos servicios (separados por coma si son varios): ");
    fflush(stdin);
    fgets(nuevo_servicio, sizeof(nuevo_servicio), stdin);
    nuevo_servicio[strcspn(nuevo_servicio, "\n")] = '\0';
    strcpy(p->servicios, nuevo_servicio);
}
void modificar_domicilio(Prestador* p) {
    char nuevo_domicilio[100];
    printf("Ingrese el nuevo domicilio: ");
    fflush(stdin);
    fgets(nuevo_domicilio, sizeof(nuevo_domicilio), stdin);
    nuevo_domicilio[strcspn(nuevo_domicilio, "\n")] = '\0';
    strcpy(p->domicilio, nuevo_domicilio);
}
void modificar_email(Prestador* p) {
    char nuevo_email[50];
    printf("Ingrese el nuevo email: ");
    fflush(stdin);
    fgets(nuevo_email, sizeof(nuevo_email), stdin);
    nuevo_email[strcspn(nuevo_email, "\n")] = '\0';
    strcpy(p->email, nuevo_email);
}
void modificar_telefono(Prestador* p) {
    char nuevo_telefono[20];
    printf("Ingrese el nuevo número de teléfono: ");
    fflush(stdin);
    fgets(nuevo_telefono, sizeof(nuevo_telefono), stdin);
    nuevo_telefono[strcspn(nuevo_telefono, "\n")] = '\0';
    strcpy(p->telefono, nuevo_telefono);
}