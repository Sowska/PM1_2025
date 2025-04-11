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

// Menu de opciones para administrar arbol Binario
void menuArbol(Arbol *arbol)
{
    int opcion, returnAlta, dni, returnBaja,resultMem;

    Prestador aux;

    do
    {
        limpiarPantalla();
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
            limpiarPantalla();

            printf("Usted selecciono: ALTA  \n\n");
            printf("Ingrese el DNI: \n");
            scanf("%d", &aux.dni);
            while (aux.dni < MINDNI || aux.dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &aux.dni);
            }
            printf("Ingrese el nombre: \n");
            scanf(" %[^\n]", aux.nombre);
            printf("Ingrese el servicio: \n");
            scanf(" %[^\n]", aux.servicios);
            printf("Ingrese el domicilio: \n");
            scanf(" %[^\n]", aux.domicilio);
            printf("Ingrese el email: \n");
            scanf(" %[^\n]", aux.email);
            printf("Ingrese el telefono: \n");
            scanf(" %[^\n]", aux.telefono);

            returnAlta = altaABBMem(arbol, aux);

            if (returnAlta)
            {
                printf("Carga exitosa.\n");
            }
            else
            {
                printf("Carga fallida.\n");
            }

            break;
        case 2:
            limpiarPantalla();

            printf("Usted selecciono: BAJA  \n\n");

            printf("Ingrese el DNI: \n");
            scanf("%d", &dni);
            while (dni < MINDNI || dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &dni);
            }
            returnBaja = bajaABBConfirmada(dni, arbol);

            switch (returnBaja)
            {
            case 0:
                printf("El prestador no existe en la lista.\n");
                break;
            case 1:
                printf("El prestador fue eliminado exitosamente.\n");
                break;
            case 2:
                printf("La lista esta vacia.\n");
                break;

            case 3:
                printf("El usuario canceló la operación.\n");
                break;
            default:
                printf("Error inesperado\n");
                break;
            }
            break;
        case 3:
            limpiarPantalla();

            printf("Usted selecciono: BUSCAR PRESTADOR (Evocar)  \n\n");
            printf("Ingrese el DNI: \n");
            scanf("%d", &dni);
            while (dni < MINDNI || dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &dni);
            }

            aux = evocarABB(arbol, dni, NULL);
            if (aux.dni == 0)
            {
                printf("El prestador no existe en la lista.\n");
            }
            else
            {
                printf("El prestador fue encontrado exitosamente.\n");
                mostrarPrestador(aux);
            }
            break;
        case 4:
            limpiarPantalla();

            printf("Usted selecciono: MOSTRAR ESTRUCTURA  \n\n");
            mostrarEstructuraABB(arbol->raiz);
            break;
        case 5:
        limpiarPantalla();

        printf("Usted selecciono: CARGAR DESDE ARCHIVO (Memorizacion Previa) \n\n");
        resultMem = memorizacionPreviaABB(arbol);
            switch (resultMem)
            {
            case 1:
                printf("Memorizacion exitosa.\n");

            case 2:
                printf("El archivo está vacío.\n");
                break;

            case 3:
                printf("No se pudo abrir el archivo\n");
            default:
                printf("Error inesperado en carga de archivo.\n");
                break;
            }
            break;
        case 6:
        limpiarPantalla();

        printf("Usted selecciono: MODIFICAR PRESTADOR  \n\n");
        printf("Ingrese el DNI: \n");
        scanf("%d", &dni);
        while (dni < MINDNI || dni > INFINITO)
        {
            printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
            scanf("%d", &dni);
        }

        modificarABB(dni, arbol);

            break;
        case 7:
            printf("Volviendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    } while (opcion != 7);
}
// Menu de opciones para administrar Lista Vinculada
void menuListaVinculada(LVO *lvo)
{
    int opcion;
    Prestador aux;
    int loc = 0, dni = 0, costonull = 0;

    do
    {
        limpiarPantalla();
        printf("\n--- LISTA VINCULADA ORDENADA---\n");
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

            limpiarPantalla();

            printf("Usted selecciono: ALTA  \n\n");

            printf("Ingrese el DNI: \n");
            scanf("%d", &aux.dni);
            while (aux.dni < MINDNI || aux.dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &aux.dni);
            }
            printf("Ingrese el nombre: \n");
            scanf(" %[^\n]", aux.nombre);
            printf("Ingrese el servicio: \n");
            scanf(" %[^\n]", aux.servicios);
            printf("Ingrese el domicilio: \n");
            scanf(" %[^\n]", aux.domicilio);
            printf("Ingrese el email: \n");
            scanf(" %[^\n]", aux.email);
            printf("Ingrese el telefono: \n");
            scanf(" %[^\n]", aux.telefono);
            loc = altaLVOMem(aux, lvo);

            switch (loc)
            {
            case 0:
                printf("El prestador ya existe en la lista.\n");
                break;

            case 1:
                printf("El prestador fue agregado exitosamente.\n");
                break;

            case 2:
                printf("Memoria insuficiente\n");
                break;

            default:
                printf("Error inesperado\n");
                break;
            }

            break;

        case 2:
            limpiarPantalla();

            printf("Usted selecciono: BAJA  \n\n");

            printf("Ingrese el DNI: \n");
            scanf("%d", &dni);
            while (dni < MINDNI || dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &dni);
            }
            loc = bajaLVOConfirmada(dni, lvo);

            switch (loc)
            {
            case 0:
                printf("El prestador no existe en la lista.\n");
                break;
            case 1:
                printf("El prestador fue eliminado exitosamente.\n");
                break;
            case 2:
                printf("La lista esta vacia.\n");
                break;

            case 3:
                printf("El usuario canceló la operación.\n");
                break;
            default:
                printf("Error inesperado\n");
                break;
            }
            break;
        case 3:
            limpiarPantalla();

            printf("Usted selecciono: BUSCAR PRESTADOR (Evocar)  \n\n");

            printf("Ingrese el DNI: \n");
            scanf("%d", &dni);
            while (dni < MINDNI || dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &dni);
            }
            aux = evocarLVO(*lvo, dni, &costonull);

            if (aux.dni == 0)
            {
                printf("El prestador no existe en la lista.\n");
            }
            else
            {
                printf("El prestador fue encontrado exitosamente.\n");
                mostrarPrestador(aux);
            }
            break;

        case 4:
            limpiarPantalla();

            printf("Usted selecciono: MOSTRAR ESTRUCTURA  \n\n");
            mostrarLista(*lvo);
            break;
        case 5:
            limpiarPantalla();

            printf("Usted selecciono: CARGAR DESDE ARCHIVO (Memorizacion Previa) \n\n");
            loc = memorizacionPrevia(lvo);
            switch (loc)
            {
            case 1:
                printf("Memorizacion exitosa.\n");

            case 2:
                printf("El archivo está vacío.\n");
                break;

            case 3:
                printf("No se pudo abrir el archivo\n");
            default:
                printf("Error inesperado en carga de archivo.\n");
                break;
            }
            break;
        case 6:
            limpiarPantalla();

            printf("Usted selecciono: MODIFICAR PRESTADOR  \n\n");

            printf("Ingrese el DNI: \n");
            scanf("%d", &dni);
            while (dni < MINDNI || dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &dni);
            }
            modificarLVO(dni, lvo);
            break;

        case 7:
            limpiarPantalla();
            printf("Volviendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    } while (opcion != 7);
}
// Menu de opciones para administrar Lista Invertida
void menuListaInvertida(LIBB* libb)
{
    int opcion, result, dni;
    Prestador aux;

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
        limpiarPantalla();

        printf("Usted selecciono: ALTA  \n\n");

        printf("Ingrese el DNI: \n");
        scanf("%d", &aux.dni);
        while (aux.dni < MINDNI || aux.dni > INFINITO)
        {
            printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
            scanf("%d", &aux.dni);
        }
        printf("Ingrese el nombre: \n");
        scanf(" %[^\n]", aux.nombre);
        printf("Ingrese el servicio: \n");
        scanf(" %[^\n]", aux.servicios);
        printf("Ingrese el domicilio: \n");
        scanf(" %[^\n]", aux.domicilio);
        printf("Ingrese el email: \n");
        scanf(" %[^\n]", aux.email);
        printf("Ingrese el telefono: \n");

        result = altaLIBB(aux, libb, NULL);
        switch (result)
        {
        case 0:
            printf("El prestador ya existe en la lista.\n");
            break;

        case 1:
            printf("El prestador fue agregado exitosamente.\n");
            break;

        case 2:
            printf("Lista llena\n");
            break;

            case 3:
            printf("Memoria insuficiente\n");
            break;

        default:
            printf("Error inesperado\n");
            break;
        }
        
            break;
        case 2:
        limpiarPantalla();

        printf("Usted selecciono: BAJA  \n\n");

        printf("Ingrese el DNI: \n");
        scanf("%d", &dni);
        while (dni < MINDNI || dni > INFINITO)
        {
            printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
            scanf("%d", &dni);
        }
        result = bajaLIBBConfirmada(dni, libb, NULL);

        switch (result)
        {
        case 0:
            printf("El prestador no existe en la lista.\n");
            break;
        case 1:
            printf("El prestador fue eliminado exitosamente.\n");
            break;
        case 2:
            printf("La lista esta vacia.\n");
            break;

        case 3:
            printf("El usuario canceló la operación.\n");
            break;
        default:
            printf("Error inesperado\n");
            break;
        }
            break;

        case 3:
            limpiarPantalla();

            printf("Usted selecciono: BUSCAR PRESTADOR (Evocar)  \n\n");

            printf("Ingrese el DNI: \n");
            scanf("%d", &dni);
            while (dni < MINDNI || dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &dni);
            }
            aux = evocarLIBB(*libb, dni, NULL);

            if (aux.dni == 0)
            {
                printf("El prestador no existe en la lista.\n");
            }
            else
            {
                printf("El prestador fue encontrado exitosamente.\n");
                mostrarPrestador(aux);
            }
            break;
        case 4:
        limpiarPantalla();

        printf("Usted selecciono: MOSTRAR ESTRUCTURA  \n\n");
            mostrarLIBBPaginada(*libb, 1, (libb->ultimo)+1);
            break;
        case 5:
        limpiarPantalla();

        printf("Usted selecciono: CARGAR DESDE ARCHIVO (Memorizacion Previa) \n\n");
        result = memorizacionPreviaLIBB(libb);
        switch (result)
        {
        case 1:
            printf("Memorizacion exitosa.\n");

        case 2:
            printf("El archivo está vacío.\n");
            break;

        case 3:
            printf("No se pudo abrir el archivo\n");

        case 4:
        printf("Lista Invertida llena\n");
            break;
        default:
            printf("Error inesperado en carga de archivo.\n");
            break;
        }
            break;
        case 6:
        limpiarPantalla();

        printf("Usted selecciono: MODIFICAR PRESTADOR  \n\n");

        printf("Ingrese el DNI: \n");
        scanf("%d", &dni);
        while (dni < MINDNI || dni > INFINITO)
        {
            printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
            scanf("%d", &dni);
        }
        modificarLIBB(dni, libb);
            break;
        case 7:
            printf("Volviendo...\n");
            break;
        default:
            printf("Opción inválida.\n");
        }
    } while (opcion != 7);
}


// funcion para cargar archivo de operaciones y costos
int cargarArchivoOperaciones(Arbol *arbol, LVO *lvo, LIBB *libb, CostosABB *costosABB, CostosLVO *costosLVO, CostosLIBB *costosLIBB)
{
    int operacion, result;
    Prestador aux, aux2;

    float costoEvocarABB = 0.0;
    float costoAltaABB = 0.0;
    float costoBajaABB = 0.0;
    int cantidadABB = 0;

    int costoEvocarLIBB= 0;
    float costoAltaLIBB= 0;
    float costoBajaLIBB= 0;
    int cantidadLIBB= 0;

    int costoEvocarLVO = 0;
    float costoAltaLVO = 0;
    float costoBajaLVO = 0;
    int cantidadLVO = 0;

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
            result = altaABB(arbol, aux, &costoAltaABB);

            if (costosABB->max[0] < costoAltaABB)
            {
                costosABB->max[0] = costoAltaABB;
            }
            if (result)
            {
                costosABB->total[0] += costoAltaABB;
                costosABB->cant[0]++;
                cantidadABB++;
            }

            // Procesar alta en LIBB
            result = altaLIBB(aux, libb, &costoAltaLIBB);

            if (costosLIBB->max[0] < costoAltaLIBB)
            {
                costosLIBB->max[0] = costoAltaLIBB;
            }
            if (result)
            {
                costosLIBB->total[0] += costoAltaLIBB;

                costosLIBB->cant[0]++;
                (cantidadLIBB)++;
            }

            // Procesar alta en LVO
            result = altaLVO(aux, lvo, &costoAltaLVO);

            if (costosLVO->max[0] < costoAltaLVO)
            {
                costosLVO->max[0] = costoAltaLVO;
            }
            if (result)
            {
                costosLVO->total[0] += costoAltaLVO;
                costosLVO->cant[0]++;
                (cantidadLVO)++;
            }

            break;

        case 2:

            result = bajaABBAutomatica(arbol, aux, &costoBajaABB);

            if (costosABB->max[1] < costoBajaABB)
            {
                costosABB->max[1] = costoBajaABB;
            }
            if (result)
            {
                costosABB->total[1] += costoBajaABB;
                costosABB->cant[1]++;
                cantidadABB--;
            }

            // Procesar baja en LIBB
            result = bajaLIBBAutomatica(aux.dni, libb, &costoBajaLIBB);

            if (costosLIBB->max[1] < costoBajaLIBB)
            {
                costosLIBB->max[1] = costoBajaLIBB;
            }
            if (result)
            {
                costosLIBB->total[1] += costoBajaLIBB;
                costosLIBB->cant[1]++;
                (cantidadLIBB)--;
            }

            // Procesar baja en LVO
            result = bajaLVOAutomatica(aux, lvo, &costoBajaLVO);

            if (costosLVO->max[1] < costoBajaLVO)
            {
                costosLVO->max[1] = costoBajaLVO;
            }
            if (result)
            {
                costosLVO->total[1] += costoBajaLVO;
                costosLVO->cant[1]++;
                cantidadLVO--;
            }

            break;

        case 3:
            // Procesar evocacion en ABB
            aux2= evocarABB(arbol, aux.dni, &costoEvocarABB);
            if (aux.dni != 0)
            {
                costosABB->total[2] += costoEvocarABB;
                costosABB->cant[2]++;
                if (costosABB->max[2] < costoEvocarABB)
                {
                    costosABB->max[2] = costoEvocarABB;
                }
            }
            else
            {
                costosABB->total[3] += costoEvocarABB;
                costosABB->cant[3]++;
                if (costosABB->max[3] < costoEvocarABB)
                {
                    costosABB->max[3] = costoEvocarABB;
                }
            }

            // Procesar evocacion en LIBB
            evocarLIBB(*libb, aux.dni, &costoEvocarLIBB);
            if (aux.dni !=0)
            {

                costosLIBB->total[2] += costoEvocarLIBB;
                costosLIBB->cant[2]++;

                if (costosLIBB->max[2] < costoEvocarLIBB)
                {
                    costosLIBB->max[2] = costoEvocarLIBB;
                }
            }
            else
            {
                costosLIBB->total[3] += costoEvocarLIBB;
                costosLIBB->cant[3]++;
                if (costosLIBB->max[3] < costoEvocarLIBB)
                {
                    costosLIBB->max[3] = costoEvocarLIBB;
                }
            }

            // Procesar evocacion en LVO
            evocarLVO(*lvo, aux.dni, &costoEvocarLVO);
            if (aux.dni!=0)
            {
                costosLVO->total[2] += costoEvocarLVO;
                costosLVO->cant[2]++;
                if (costosLVO->max[2] < costoEvocarLVO)
                {
                    costosLVO->max[2] = costoEvocarLVO;
                }
            }
            else
            {
                costosLVO->total[3] += costoEvocarLVO;
                costosLVO->cant[3]++;
                if (costosLVO->max[3] < costoEvocarLVO)
                {
                    costosLVO->max[3] = costoEvocarLVO;
                }
            }
            break;

        default:
            printf("La operacion %d no es valida\n", operacion);
            exit(1);
        }
        operacion = 0;
    }

    fclose(fp);

            // Para costosABB
            if (costosABB->cant[0] > 0)
                costosABB->med[0] = costosABB->total[0] / costosABB->cant[0];

            if (costosABB->cant[1] > 0)
                costosABB->med[1] = costosABB->total[1] / costosABB->cant[1];

            if (costosABB->cant[2] > 0)
                costosABB->med[2] = costosABB->total[2] / costosABB->cant[2];

            if (costosABB->cant[3] > 0)
                costosABB->med[3] = costosABB->total[3] / costosABB->cant[3];


            // Para costosLIBB
            if (costosLIBB->cant[0] > 0)
                costosLIBB->med[0] = (float)costosLIBB->total[0] / costosLIBB->cant[0];

            if (costosLIBB->cant[1] > 0)
                costosLIBB->med[1] = (float)costosLIBB->total[1] / costosLIBB->cant[1];

            if (costosLIBB->cant[2] > 0)
                costosLIBB->med[2] = (float)costosLIBB->total[2] / costosLIBB->cant[2];


            if (costosLIBB->cant[3] > 0)
                costosLIBB->med[3] = (float)costosLIBB->total[3] / costosLIBB->cant[3];


            // Para costosLVO
            if (costosLVO->cant[0] > 0)
                costosLVO->med[0] = (float)costosLVO->total[0] / costosLVO->cant[0];

            if (costosLVO->cant[1] > 0)
                costosLVO->med[1] = (float)costosLVO->total[1] / costosLVO->cant[1];


            if (costosLVO->cant[2] > 0)
                costosLVO->med[2] = (float)costosLVO->total[2] / costosLVO->cant[2];

            if (costosLVO->cant[3] > 0)
                costosLVO->med[3] = (float)costosLVO->total[3] / costosLVO->cant[3];

                return 1;
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

    resultCarga = cargarArchivoOperaciones(arbol, lvo, libb, costosABB, costosLVO, costosLIBB);

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

    if (resultCarga == 1)
    {

        mostrarCostosABB(*costosABB);
        mostrarCostosLVO(*costosLVO);
        mostrarCostosLIBB(*costosLIBB);
    }
}

// Menu de administracion de estructuras
void administrarEstructura(Arbol *arbol, LVO *lvo, LIBB *libb)
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
            menuListaVinculada(lvo);
            break;
        case 2:
            menuArbol(arbol);
            break;
        case 3:
            menuListaInvertida(libb);
            break;
        case 4:
            printf("Volviendo al menú principal...\n");
            break;
        default:
            printf("Opción inválida, intente nuevamente.\n");
        }
    } while (opcion != 4);
}




int main()
{

    // creo las estructuras
    LVO lvo;
    Arbol arbol;
    LIBB libb;

    // inicio las estructuras
    inicializarLista(&lvo);
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

            compararEstructuras(&libb, &lvo, &arbol, &costosABB, &costosLVO, &costosLIBB);
            printf("Comparacion de estructuras finalizada.\n");

            break;
        case 2:
            limpiarPantalla();
            printf("Usted selecciono: ADMINISTRAR ESTRUCTURAS\n\n");
            administrarEstructura(&arbol, &lvo, &libb);
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
