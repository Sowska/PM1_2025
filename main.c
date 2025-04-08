#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LIBB.h"
#include "Prestador.h"
#include "Resultloc.h"
#define MINDNI 10000000
#define INFINITO 99999999

int main()
{
    int cant=0;
    Prestador *prestador[MAX];
    int opcion=1;
    int cargaaux;

 do
    {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Comparar estructuras\n");
        printf("2. Administrar estructura\n");
        printf("3. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            compararEstructuras();
            break;
        case 2:
            administrarEstructura();
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción inválida, intente nuevamente.\n");
        }
    }
    while(opcion != 3);

    return 0;
}

// Función para comparar estructuras (puedes implementar lógica aquí)
void compararEstructuras()
{
    printf("\nFuncionalidad de comparación en desarrollo...\n");
}

// Menú de administración de estructuras
void administrarEstructura()
{
    int opcion;

    do
    {
        printf("\n--- ADMINISTRAR ESTRUCTURA ---\n");
        printf("1. Lista Vinculada\n");
        printf("2. Árbol Binario\n");
        printf("3. Lista Invertida\n");
        printf("4. Volver al menú principal\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            menuListaVinculada();
            break;
        case 2:
            menuArbol();
            break;
        case 3:
            menuListaInvertida();
            break;
        case 4:
            printf("Volviendo al menú principal...\n");
            break;
        default:
            printf("Opción inválida, intente nuevamente.\n");
        }
    }
    while(opcion != 4);
}

// Menú de opciones para Lista Vinculada
void menuListaVinculada()
{
    int opcion;

    do
    {
        printf("\n--- LISTA VINCULADA ---\n");
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Evocar\n");
        printf("4. Mostrar estructura\n");
        printf("5. Memorización previa\n");
        printf("6. Modificar\n");
        printf("7. Volver al menú anterior\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            alta();
            break;
        case 2:
            baja();
            break;
        case 3:
            evocar();
            break;
        case 4:
            mostrarEstructura();
            break;
        case 5:
            memorizacionPrevia();
            break;
        case 6:
            modificar();
            break;
        case 7:
            printf("Volviendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    }
    while(opcion != 7);
}

// Menú de opciones para Árbol Binario
void menuArbol()
{
    int opcion;

    do
    {
        printf("\n--- ÁRBOL BINARIO ---\n");
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Evocar\n");
        printf("4. Mostrar estructura\n");
        printf("5. Memorización previa\n");
        printf("6. Modificar\n");
        printf("7. Volver al menú anterior\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            alta();
            break;
        case 2:
            baja();
            break;
        case 3:
            evocar();
            break;
        case 4:
            mostrarEstructura();
            break;
        case 5:
            memorizacionPrevia();
            break;
        case 6:
            modificar();
            break;
        case 7:
            printf("Volviendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    }
    while(opcion != 7);
}

// Menú de opciones para Lista Invertida
void menuListaInvertida()
{
    int opcion;

    do
    {
        printf("\n--- LISTA INVERTIDA ---\n");
        printf("1. Alta\n");
        printf("2. Baja\n");
        printf("3. Evocar\n");
        printf("4. Mostrar estructura\n");
        printf("5. Memorización previa\n");
        printf("6. Modificar\n");
        printf("7. Volver al menú anterior\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            altaLIBB();
            break;
        case 2:
            bajaLIBB();
            break;
        case 3:
            evocar();
            break;
        case 4:
            mostrarEstructura();
            break;
        case 5:
            cargarArchivoLIBB();
            break;
        case 6:
            ModificarLIBB();
            break;
        case 7:
            printf("Volviendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    }
    while(opcion != 7);
}