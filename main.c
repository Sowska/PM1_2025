#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Constantes.h"
#include "Prestador.h"
#include "Resultloc.h"
#include "Costos.h"

#include "LIBB.h"
#include "LVO.h"
#include "ABB.h"

int main()
{

    // creo las estructuras
    LVO lvo;
    Arbol arbol;
    LIBB libb;

    // inicio las estructuras
    initLVO(&lvo);
    initArbol(&arbol);
    initLIBB(&libb);
    int opcion = 0;

    // Inicializar variables de costos
    CostosABB costosABB = {0};
    CostosLVO costosLVO = {0};
    CostosLIBB costosLIBB = {0};

    // Menu principal
    do
    {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Comparar estructuras\n");
        printf("2. Administrar estructura\n");
        printf("3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            limpiarPantalla();
            printf("Usted selecciono: COMPARACION DE ESTRUCTURAS\n\n");

            compararEstructuras(&libb, &lvo, &arbol);
            break;
        case 2:
            administrarEstructura();
            break;
        case 3:
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción invalida, intente nuevamente.\n");
        }
    } while (opcion != 3);

    return 0;
}

// funcion para cargar archivo de operaciones y costos
cargarArchivoOperaciones(Arbol *arbol, LVO *lvo, LIBB *libb, CostosABB *costosABB, CostosLVO *costosLVO, CostosLIBB *costosLIBB)
{
    int operacion, result;
    Prestador aux;

    FILE *fp = fopen("Operaciones-Prestadores.txt", "r");
    if (fp == NULL)
    {
        return 3; // archivo no encontrado
    }
 
    fseek(fp, 0, SEEK_END);

    if (ftell(fp) == 0)
    {
        fclose(fp);
        return 2; // archivo vacio
    }

    rewind(fp);

    while (!feof(fp))
    {
        fscanf(fp, " %d", &operacion);
        fscanf(fp, "%d\n", &aux.dni);

        if (operacion == 1 || operacion == 2)
        {
            fscanf(fp, "%[^\n]\n", aux.nombre);
            fscanf(fp, "%[^\n]\n", aux.servicios);
            fscanf(fp, "%[^\n]\n", aux.domicilio);
            fscanf(fp, "%[^\n]\n", aux.email);
            fscanf(fp, "%[^\n]\n", aux.telefono);
        }

        switch (operacion)
        {
        case 1:

            // Procesar alta en ABB
            result = altaABB(arbol, aux, costoAltaABB, *cantidadABB);

            if (costosABB->max[0] < *costoAltaABB)
            {
                costosABB->max[0] = *costoAltaABB;
            }
            if (result)
            {
                costosABB->total[0] += *costoAltaABB;
                costosABB->cant[0]++;
                (*cantidadABB)++;
            }

            // Procesar alta en LIBB
            result = altaLIBB(listaBB, aux, costoAltaLSOBB);

            if (costosLSOBB->max[0] < *costoAltaLSOBB)
            {
                costosLSOBB->max[0] = *costoAltaLSOBB;
            }
            if (result)
            {
                costosLSOBB->total[0] += *costoAltaLSOBB;

                costosLSOBB->cant[0]++;
                (*cantidadLSOBB)++;
            }

                // Procesar alta en LVO
                result = altaLVO(LSO, aux, *cantidadLSO, costoAltaLSO);

                if (costosLSO->max[0] < *costoAltaLSO)
                {
                    costosLSO->max[0] = *costoAltaLSO;
                }
                if (result)
                {
                    costosLSO->total[0] += *costoAltaLSO;
                    costosLSO->cant[0]++;
                    (*cantidadLSO)++;
                }


            break;


        case 2:

            result = bajaABB(arbol, aux, costoBajaABB);

            if (costosABB->max[1] < *costoBajaABB)
            {
                costosABB->max[1] = *costoBajaABB;
            }
            if (result)
            {
                costosABB->total[1] += *costoBajaABB;
                costosABB->cant[1]++;
                (*cantidadABB)--;
            }

            // Procesar baja en LIBB
            result = bajaLSOBB(listaBB, aux, costoBajaLSOBB);

            if (costosLSOBB->max[1] < *costoBajaLSOBB)
            {
                costosLSOBB->max[1] = *costoBajaLSOBB;
            }
            if (result)
            {
                costosLSOBB->total[1] += *costoBajaLSOBB;
                costosLSOBB->cant[1]++;
                (*cantidadLSOBB)--;
            }

            // Procesar baja en LVO
            result = bajaLSO(LSO, aux, *cantidadLSO, costoBajaLSO);

            if (costosLSO->max[1] < *costoBajaLSO)
            {
                costosLSO->max[1] = *costoBajaLSO;
            }
            if (result)
            {
                costosLSO->total[1] += *costoBajaLSO;
                costosLSO->cant[1]++;
                (*cantidadLSO)--;
            }

            break;

        case 3:
            // Procesar evocación en ABB
            evocarABB(arbol, aux.dni, &exito, costoEvocarABB);
            if (exito)
            {
                costosABB->total[2] += *costoEvocarABB;
                costosABB->cant[2]++;
                if (costosABB->max[2] < *costoEvocarABB)
                {
                    costosABB->max[2] = *costoEvocarABB;
                }
            }
            else
            {
                costosABB->total[3] += *costoEvocarABB;
                costosABB->cant[3]++;
                if (costosABB->max[3] < *costoEvocarABB)
                {
                    costosABB->max[3] = *costoEvocarABB;
                }
            }

            // Procesar evocacion en LIBB
            evocarLSOBB(*listaBB, aux.dni, &exito, costoEvocarLSOBB);
            if (exito)
            {

                costosLSOBB->total[2] += *costoEvocarLSOBB;
                costosLSOBB->cant[2]++;

                if (costosLSOBB->max[2] < *costoEvocarLSOBB)
                {
                    costosLSOBB->max[2] = *costoEvocarLSOBB;
                }
            }
            else
            {
                costosLSOBB->total[3] += *costoEvocarLSOBB;
                costosLSOBB->cant[3]++;
                if (costosLSOBB->max[3] < *costoEvocarLSOBB)
                {
                    costosLSOBB->max[3] = *costoEvocarLSOBB;
                }
            }

            // Procesar evocacion en LVO
            evocarLSO(LSO, aux.dni, &exito, costoEvocarLSO);
            if (exito)
            {
                costosLSO->total[2] += *costoEvocarLSO;
                costosLSO->cant[2]++;
                if (costosLSO->max[2] < *costoEvocarLSO)
                {
                    costosLSO->max[2] = *costoEvocarLSO;
                }
            }
            else
            {
                costosLSO->total[3] += *costoEvocarLSO;
                costosLSO->cant[3]++;
                if (costosLSO->max[3] < *costoEvocarLSO)
                {
                    costosLSO->max[3] = *costoEvocarLSO;
                }
            }
            break;

        default:
            printf("La operacion %d no es valida\n", operacion);
            exit(1);
        }
        operacion = 0;
    }
}
// Funcion para comparar estructuras
void compararEstructuras(LIBB *libb, LVO *lvo, Arbol *arbol, CostosABB *costosABB, CostosLVO *costosLVO, CostosLIBB *costosLIBB)
{
    int resultCarga;

    vaciarArbol(arbol);
    liberarLIBB(libb);
    liberarLista(lvo);

    // poner en 0 las variables que tienen que ver con la carga
    memset(&costosABB, 0, sizeof(costosABB));
    memset(&costosLVO, 0, sizeof(costosLVO));
    memset(&costosLIBB, 0, sizeof(costosLIBB));

    // llamar la carga del archivo y notificar al usuario en base a la salida de la operacion

    resultCarga = cargarArchivoOperaciones(&arbol, &lvo, &libb, costosABB, costosLVO, costosLIBB);

    switch (resultCarga)
    {
    case 1:
        printf("Carga exitosa del archivo!\n");

        break;

    case 2:
        printf("Archivo vacio\n");
        break;

    case 3:
        printf("Archivo invalido\n");
        break;

    default:
        printf("Error inesperado\n");
        break;
    }

    if (resultCarga==1)
    {

        mostrarCostosABB(costosABB);
        mostrarCostosLSOBB(costosLVO);
        mostrarCostosLSO(costosLIBB);
    }
}

// Menu de administracion de estructuras
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

        switch (opcion)
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
    } while (opcion != 4);
}

// Menu de opciones para administrar Lista Vinculada
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

        switch (opcion)
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
    } while (opcion != 7);
}

// Menu de opciones para administrar arbol Binario
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

        switch (opcion)
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
    } while (opcion != 7);
}

// Menu de opciones para administrar Lista Invertida
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

        switch (opcion)
        {
        case 1:
            altaLIBB() break;
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
    } while (opcion != 7);
}