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
    int opcion=0, resultadoAlta = 0, resultadoBaja = 0, resultadoMem = 0, dni = 0;
    float costonull = 0.0;
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
            getchar();
            printf("Ingrese el nombre:\n");
            fgets(aux.nombre, sizeof(aux.nombre), stdin);
            aux.nombre[strcspn(aux.nombre, "\n")] = 0; // Elimino '\n' final

            printf("Ingrese el servicio:\n");
            fgets(aux.servicios, sizeof(aux.servicios), stdin);
            aux.servicios[strcspn(aux.servicios, "\n")] = 0;

            printf("Ingrese el domicilio:\n");
            fgets(aux.domicilio, sizeof(aux.domicilio), stdin);
            aux.domicilio[strcspn(aux.domicilio, "\n")] = 0;

            printf("Ingrese el email:\n");
            fgets(aux.email, sizeof(aux.email), stdin);
            aux.email[strcspn(aux.email, "\n")] = 0;

            printf("Ingrese el teléfono:\n");
            fgets(aux.telefono, sizeof(aux.telefono), stdin);
            aux.telefono[strcspn(aux.telefono, "\n")] = 0;

            resultadoAlta = altaABB(arbol, aux,&costonull);

            if (resultadoAlta==0)
            {
               
                printf("Carga fallida.\n");
            }
            else
            {
                printf("Carga exitosa.\n");
            }

            printf("Presione ENTER para continuar...");
            getchar(); // <-- Este ahora sí esperará al usuario

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
            getchar();
            Prestador auxP = {dni, "", "", "", "", ""};
            resultadoBaja = bajaABB(auxP, arbol,1,&costonull);

            switch (resultadoBaja)
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
            printf("Presione ENTER para continuar...\n");
            char enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
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
            getchar();
            
            aux = evocarABB(arbol, dni, &costonull);
            if (aux.dni == 0)
            {
                printf("El prestador no existe en la lista.\n");
            }
            else
            {
                printf("El prestador fue encontrado exitosamente.\n");
                mostrarPrestador(aux);
            }
            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
            }
            break;
        case 4:
            limpiarPantalla();

            printf("Usted selecciono: MOSTRAR ESTRUCTURA  \n\n");
            mostrarEstructuraABB(arbol->raiz);
            getchar();
            printf("Presione ENTER para continuar...\n");
            getchar();
            break;
        case 5:
            limpiarPantalla();
            printf("Usted selecciono: CARGAR DESDE ARCHIVO (Memorizacion Previa) \n\n");
            resultadoMem = memorizacionPreviaABB(arbol);
            getchar();
            switch (resultadoMem)
            {
            case 1:
                printf("Memorizacion exitosa.\n");

                break;
            case 2:
                printf("El archivo está vacío.\n");
                break;

            case 3:
                printf("No se pudo abrir el archivo\n");
            default:
                printf("Error inesperado en carga de archivo.\n");
                break;
            }
            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
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
            getchar();

            modificarABB(dni, arbol);
            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
            }


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
// Menu de opciones para administrar Lista Vinculada
void menuListaVinculada(LVO *lvo)
{
    int opcion;
    Prestador aux;
    int resultadoAlta = 0, resultadoBaja = 0, resultadoMem = 0, dni = 0;
    float costonull = 0.0;
    char enter = 0;

    do
    {
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
            getchar();
            while (aux.dni < MINDNI || aux.dni > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &aux.dni);
            }
            printf("Ingrese el nombre:\n");
            fgets(aux.nombre, sizeof(aux.nombre), stdin);
            aux.nombre[strcspn(aux.nombre, "\n")] = 0; // Elimino '\n' final

            printf("Ingrese el servicio:\n");
            fgets(aux.servicios, sizeof(aux.servicios), stdin);
            aux.servicios[strcspn(aux.servicios, "\n")] = 0;

            printf("Ingrese el domicilio:\n");
            fgets(aux.domicilio, sizeof(aux.domicilio), stdin);
            aux.domicilio[strcspn(aux.domicilio, "\n")] = 0;

            printf("Ingrese el email:\n");
            fgets(aux.email, sizeof(aux.email), stdin);
            aux.email[strcspn(aux.email, "\n")] = 0;

            printf("Ingrese el teléfono:\n");
            fgets(aux.telefono, sizeof(aux.telefono), stdin);
            aux.telefono[strcspn(aux.telefono, "\n")] = 0;
            
            resultadoAlta = altaLVO(aux, lvo, &costonull);

            switch (resultadoAlta)
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
            printf("Presione ENTER para continuar...");
            getchar(); // <-- Este ahora sí esperará al usuario
            break;

        case 2:
            limpiarPantalla();

            printf("Usted selecciono: BAJA  \n\n");
            int auxDNI = 0;
            printf("Ingrese el DNI: \n");
            scanf("%d", &auxDNI);

            while (auxDNI < MINDNI || auxDNI > INFINITO)
            {
                printf("DNI invalido. Debe ser un numero positivo de 8 digitos.\n");
                scanf("%d", &auxDNI);
            }
            getchar(); // Limpiar el buffer de entrada
            Prestador auxP = {auxDNI, "", "", "", "", ""};
            resultadoBaja = bajaLVO(auxP, lvo, &costonull, 1);

            switch (resultadoBaja)
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

            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
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
            getchar(); // Limpiar el buffer de entrada
            aux = evocarLVO(*lvo, dni, &costonull);

            if (aux.dni == 0)
            {
                printf("El prestador no existe en la lista.\n");
                getchar();
            }
            else
            {
                printf("Prestador encontrado:\n");
                mostrarPrestador(aux);
            }
            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
            }
            break;

        case 4:
            limpiarPantalla();

            printf("Usted selecciono: MOSTRAR ESTRUCTURA  \n\n");
            mostrarLista(*lvo);
            getchar();
            printf("Presione ENTER para continuar...\n");
getchar();

            break;
        case 5:
            limpiarPantalla();

            printf("Usted selecciono: CARGAR DESDE ARCHIVO (Memorizacion Previa) \n\n");
            resultadoMem = memorizacionPrevia(lvo);
            getchar();
            switch (resultadoMem)
            {
            case 1:
                printf("Memorizacion exitosa.\n");

                break;

            case 2:
                printf("El archivo está vacío.\n");
                break;

            case 3:
                printf("No se pudo abrir el archivo\n");
            default:
                printf("Error inesperado en carga de archivo.\n");
                break;
            }
            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
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
            getchar(); // Limpiar el buffer de entrada
            modificarLVO(dni, lvo);

            printf("Presione ENTER para continuar...\n");
            enter = 0;
            while (enter != '\r' && enter != '\n')
            {
                enter = getchar();
            }

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
void menuListaInvertida(LIBB *libb)
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

            float costoAlta = 0.0;
            result = altaLIBB(aux, libb, &costoAlta);
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
            float costoBaja = 0.0;
            result = bajaLIBBConfirmada(dni, libb, &costoBaja);

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
            float costoEvocar = 0.0;
            aux = evocarLIBB(*libb, dni, &costoEvocar);

            if (aux.dni == 0)
            {
                printf("El prestador no existe en la lista.\n");
            }
            else
            {
                printf("El prestador fue encontrado exitosamente.\n");
                mostrarPrestador(aux);
            }
            getchar();
            break;
        case 4:
            limpiarPantalla();

            printf("Usted selecciono: MOSTRAR ESTRUCTURA  \n\n");
            mostrarLIBBPaginada(*libb, 1, (libb->ultimo) + 1);
            getchar();
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
int cargarArchivoOperaciones(Arbol *arbol, LVO *lvo, LIBB *libb, CostosGlobales *costosGlobales)
{
    int operacion, result;
    float costoOperacion = 0.0;
    Prestador aux, aux2;

    FILE *fp = fopen("Operaciones-Prestadores2.txt", "r");
    if (fp == NULL)
        return 3; // Archivo no encontrado

    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0)
    {
        fclose(fp);
        return 2; // Archivo vacío
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
        case 1: // ALTA
            // ABB
            costoOperacion = 0.0;
            result = altaABB(arbol, aux, &costoOperacion);
            if (result == 1)
            {
                costosGlobales->abb.totalAlta += costoOperacion;
                costosGlobales->abb.cantAlta++;
                if (costoOperacion > costosGlobales->abb.maxAlta)
                    costosGlobales->abb.maxAlta = costoOperacion;
            }

            // LIBB
            costoOperacion = 0.0;
            result = altaLIBB(aux, libb, &costoOperacion);
            if (result == 1) // Solo contar si fue exitosa (1)
            {

                costosGlobales->libb.totalAlta += costoOperacion;
                costosGlobales->libb.cantAlta++;
                if (costoOperacion > costosGlobales->libb.maxAlta)
                    costosGlobales->libb.maxAlta = costoOperacion;
            }

            // LVO
            costoOperacion = 0.0;
            result = altaLVO(aux, lvo, &costoOperacion);
            if (result == 1) // Solo contar si fue exitosa (1)
            {
                costosGlobales->lvo.totalAlta += costoOperacion;
                costosGlobales->lvo.cantAlta++;
                if (costoOperacion > costosGlobales->lvo.maxAlta)
                    costosGlobales->lvo.maxAlta = costoOperacion;
                lvo->size++;
            }
            break;

        case 2: // BAJA
            // ABB
            costoOperacion = 0.0;
            result = bajaABB(aux, arbol, 0, &costoOperacion);
            if (result == 1)
            {
                costosGlobales->abb.totalBaja += costoOperacion;
                costosGlobales->abb.cantBaja++;
                if (costoOperacion > costosGlobales->abb.maxBaja)
                    costosGlobales->abb.maxBaja = costoOperacion;
            }

            // LIBB
            costoOperacion = 0.0;
            result = bajaLIBBAutomatica(aux.dni, libb, &costoOperacion);
            if (result == 1) // Solo contar si fue exitosa (1)
            {
                costosGlobales->libb.totalBaja += costoOperacion;
                costosGlobales->libb.cantBaja++;
                if (costoOperacion > costosGlobales->libb.maxBaja)
                    costosGlobales->libb.maxBaja = costoOperacion;
            }

            // LVO
            costoOperacion = 0.0;
            result = bajaLVO(aux, lvo, &costoOperacion, 0);
            if (result == 1) // Solo contar si fue exitosa (1)
            {
                costosGlobales->lvo.totalBaja += costoOperacion;
                costosGlobales->lvo.cantBaja++;
                if (costoOperacion > costosGlobales->lvo.maxBaja)
                    costosGlobales->lvo.maxBaja = costoOperacion;
                lvo->size--;
            }
            break;

        case 3: // EVOCACIOn
            // ABB
            costoOperacion = 0.0;
            aux2 = evocarABB(arbol, aux.dni, &costoOperacion);
            if (aux2.dni == 0)
            {
                costosGlobales->abb.totalEvocacionFallida += costoOperacion;
                costosGlobales->abb.cantEvocacionFallida++;
                if (costoOperacion > costosGlobales->abb.maxEvocacionFallida)
                    costosGlobales->abb.maxEvocacionFallida = costoOperacion;
            }
            else
            {
                    costosGlobales->abb.totalEvocacionExitosa += costoOperacion;
                    costosGlobales->abb.cantEvocacionExitosa++;
                    if (costoOperacion > costosGlobales->abb.maxEvocacionExitosa)
                        costosGlobales->abb.maxEvocacionExitosa = costoOperacion;
            }

            // LIBB
            costoOperacion = 0.0;
            aux2 = evocarLIBB(*libb, aux.dni, &costoOperacion);
            if (aux2.dni != 0)
            {
                costosGlobales->libb.totalEvocacionExitosa += costoOperacion;
                costosGlobales->libb.cantEvocacionExitosa++;
                if (costoOperacion > costosGlobales->libb.maxEvocacionExitosa)
                    costosGlobales->libb.maxEvocacionExitosa = costoOperacion;
            }
            else
            {
                costosGlobales->libb.totalEvocacionFallida += costoOperacion;
                costosGlobales->libb.cantEvocacionFallida++;
                if (costoOperacion > costosGlobales->libb.maxEvocacionFallida)
                    costosGlobales->libb.maxEvocacionFallida = costoOperacion;
            }

            // LVO
            costoOperacion = 0.0;
            aux2 = evocarLVO(*lvo, aux.dni, &costoOperacion);
            if (aux2.dni == 0)
            {
                costosGlobales->lvo.totalEvocacionFallida += costoOperacion;
                costosGlobales->lvo.cantEvocacionFallida++;
                if (costoOperacion > costosGlobales->lvo.maxEvocacionFallida)
                    costosGlobales->lvo.maxEvocacionFallida = costoOperacion;
            }
            else
            {
                    costosGlobales->lvo.totalEvocacionExitosa += costoOperacion;
                    costosGlobales->lvo.cantEvocacionExitosa++;
                    if (costoOperacion > costosGlobales->lvo.maxEvocacionExitosa)
                        costosGlobales->lvo.maxEvocacionExitosa = costoOperacion;
            }
            break;

        default:
            printf("La operación %d no es válida\n", operacion);
            return 4;
        }
    }

    fclose(fp);

    calculoPromediosCostos(costosGlobales);

    return 1;
}

// Funcion para comparar estructuras
void compararEstructuras(LIBB *libb, LVO *lvo, Arbol *arbol, CostosGlobales *costosGlobales)
{
    vaciarArbol(arbol);
    liberarLIBB(libb);
    liberarLista(lvo);

    inicializarCostos(costosGlobales);

    int resultCarga = cargarArchivoOperaciones(arbol, lvo, libb, costosGlobales);

    switch (resultCarga)
    {
    case 1:
        printf("Carga exitosa del archivo!\n");
        mostrarCostosGlobales(*costosGlobales);
        getchar();
        break;

    case 2:
        printf("Archivo vacío\n");
        break;

    case 3:
        printf("Archivo inválido\n");
        break;

    default:
        printf("Error inesperado\n");
        break;
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
    CostosGlobales costos = {
        .lvo = {0},
        .libb = {0},
        .abb = {0}};

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

            compararEstructuras(&libb, &lvo, &arbol, &costos);
            printf("Comparacion de estructuras finalizada.\n");

            printf("Presione ENTER para continuar...\n");
            getchar(); // Limpiar el buffer de entrada

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
