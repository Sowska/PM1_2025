#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Prestador.h"
#include "Resultloc.h"
#include "LVO.h"
#include "Constantes.h"
#include "Costos.h"

void inicializarLista(LVO *lista)
{
    lista->head = NULL; // La lista comienza vacia
    lista->size = 0;    // Tamaño inicial es 0
}



resultLocLVO localizarLVO(LVO lista, int dni, int *costo)
{
    resultLocLVO loc;
    loc.exito = 0;
    NodoLista *actual = lista.head;
    NodoLista *anterior = NULL; // importante el set en null para insertar el primero
    (*costo) = 0;

    if (lista.head == NULL) // Si la lista esta vacia
    {
        loc.pos = NULL; // No hay elementos
        loc.pre = NULL;
        return loc;
    }

    while (actual != NULL && actual->prestador.dni < dni)
    {
        anterior = actual;
        actual = actual->siguiente;
        (*costo)++;
    }

    loc.exito = (actual != NULL && actual->prestador.dni == dni); // Si el dni coincide, exito es 1

    loc.pos = actual;
    loc.pre = anterior;
    (*costo)++;

    return loc;
}

int altaLVOMem(Prestador prestador, LVO *lista) // la llamo con &costo
{
    int costoloc = 0;
    if (lista->size == MAX)
    {
        return 2; // Lista llena
    }

    resultLocLVO aux = localizarLVO(*lista, prestador.dni, &costoloc);
    if (aux.exito)
    {
        return 0; // El elemento ya existe
    }

    NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
    if (!nuevoNodo)
    {
        return 3; // Memoria insuficiente
    }

    nuevoNodo->prestador = prestador;
    nuevoNodo->siguiente = NULL;

    if (aux.pre == NULL) // Insertar al principio
    {
        nuevoNodo->siguiente = aux.pos;
        lista->head = nuevoNodo;
    }
    else if (aux.pos == NULL) // Insertar al final
    {
        aux.pre->siguiente = nuevoNodo;
    }
    else // Insertar en el medio
    {
        aux.pre->siguiente = nuevoNodo;
        nuevoNodo->siguiente = aux.pos;
    }

    lista->size++;
    return 1; // Alta exitosa
}

int altaLVO(Prestador prestador, LVO *lista, float *costo) // la llamo con &costo
{
    (*costo) = 0; // Inicializo el costo a 0
    int costoloc = 0;

    resultLocLVO aux = localizarLVO(*lista, prestador.dni, &costoloc);
    if (aux.exito)
    {
        return 0; // El elemento ya existe
    }

    NodoLista *nuevoNodo = (NodoLista *)malloc(sizeof(NodoLista));
    if (!nuevoNodo)
    {
        return 2; // Memoria insuficiente
    }

    nuevoNodo->prestador = prestador;
    nuevoNodo->siguiente = NULL;

    if (aux.pre == NULL) // Insertar al principio
    {
        nuevoNodo->siguiente = aux.pos;
        lista->head = nuevoNodo;
        (*costo) += 0.5;
    }
    else if (aux.pos == NULL) // Insertar al final
    {
        aux.pre->siguiente = nuevoNodo;
        (*costo) += 0.5;
    }
    else // Insertar en el medio
    {
        aux.pre->siguiente = nuevoNodo;
        nuevoNodo->siguiente = aux.pos;
        (*costo)++;
    }

    lista->size++;
    return 1; // Alta exitosa
}
int bajaLVOConfirmada(int dni, LVO *lista)
{
    int costoloc = 0;
    int opcion = 0;

    if (lista->head == NULL)
    {
        return 2; // Lista vacia
    }

    resultLocLVO aux = localizarLVO(*lista, dni, &costoloc);
    if (!aux.exito)
    {
        return 0; // El elemento no existe
    }

    do
    {
        printf("El prestador encontrado es:\n");
        mostrarPrestador(aux.pos->prestador);
        printf("¿Desea eliminarlo? (1: Si, 2: No): ");
        scanf("%d", &opcion);
    } while (opcion != 1 && opcion != 2);

    switch (opcion)
    {
    case 1:

        if (aux.pre == NULL)
        { // El nodo a eliminar es el primero
            lista->head = aux.pos->siguiente;
        }
        else
        {
            aux.pre->siguiente = aux.pos->siguiente; // el anterior ahora salta al siguiente del nodo que quiero borrar
        }
        free(aux.pos); // Libero la memoria del nodo eliminado
        lista->size--;
        break;

    default:
        return 3; // Baja cancelada
        break;
    }

    return 1; // Baja exitosa
}
int bajaLVOAutomatica(Prestador prestador, LVO *lista, float *costo)
{

    (*costo) = 0; // Inicializo el costo a 0
    int costoloc = 0;
    int opcion = 0;

    if (lista->head == NULL)
    {
        return 2; // Lista vacia
    }

    resultLocLVO aux = localizarLVO(*lista, prestador.dni, &costoloc);
    if (!aux.exito)
    {
        return 0; // El elemento no existe
    }

    if (sonDiferentes(aux.pos->prestador, prestador))
    {
        return 3; // El prestador a eliminar es diferente al que se busca
    }

    if (aux.pre == NULL)
    { // El nodo a eliminar es el primero
        lista->head = aux.pos->siguiente;
    }
    else
    {
        aux.pre->siguiente = aux.pos->siguiente; // el anterior ahora salta al siguiente del nodo que quiero borrar
    }
    free(aux.pos);
    (*costo) += 0.5;
    lista->size--;

    return 1; // Baja exitosa
}

void modificarLVO(int dni, LVO *lista)
{
    int opmod = 0;
    resultLocLVO resultado = localizarLVO(*lista, dni, NULL);
    if (resultado.exito)
    {
        printf("El prestador encontrado es:\n");
        mostrarPrestador(resultado.pos->prestador);

        do{
        printf("\n Que campo del prestador usted desea modificar?\n\n");
        printf("1-Nombre\n2-Servicio\n3-Domicilio\n4-Email\n5-Telefono\n");
        printf("Si desea modificar todos los campos, ingrese 6 \n");
        scanf("%d", &opmod);
        }while (opmod < 0 || opmod > 6);

        switch (opmod)
        {
        case 1:
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\n]", resultado.pos->prestador.nombre);
            printf("Modificación exitosa.\n");
            
            break;
        case 2:
            printf("Ingrese el nuevo servicio: ");
            scanf(" %[^\n]", resultado.pos->prestador.servicios);
            printf("Modificación exitosa.\n");
            break;
        case 3:
            printf("Ingrese el nuevo domicilio: ");
            scanf(" %[^\n]", resultado.pos->prestador.domicilio);
            printf("Modificación exitosa.\n");
            break;
        case 4:
            printf("Ingrese el nuevo email: ");
            scanf(" %[^\n]", resultado.pos->prestador.email);
            printf("Modificación exitosa.\n");
            break;
        case 5:
        printf("Ingrese el nuevo telefono: ");
            scanf(" %[^\n]", resultado.pos->prestador.telefono);
            printf("Modificación exitosa.\n");
            break;
        case 6:
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\n]", resultado.pos->prestador.nombre);
            printf("Ingrese el nuevo servicio: ");
            scanf(" %[^\n]", resultado.pos->prestador.servicios);
            printf("Ingrese el nuevo domicilio: ");
            scanf(" %[^\n]", resultado.pos->prestador.domicilio);
            printf("Ingrese el nuevo email: ");
            scanf(" %[^\n]", resultado.pos->prestador.email);
            printf("Ingrese el nuevo telefono: ");
            scanf(" %[^\n]", resultado.pos->prestador.telefono);
            
            printf("Modificación exitosa.\n");
            break;


        default:
        printf("Error inesperado\n");
            break;
        }
        
    } else
    {
        printf("El prestador no fue encontrado\n");
    }


}

Prestador evocarLVO(LVO lista, int dni, int *costo)
{
    Prestador prestador;
    resultLocLVO aux = localizarLVO(lista, dni, costo);
    if (aux.exito)
    {
        prestador = aux.pos->prestador; // Retorna el prestador encontrado
    }
    else
    {
        prestador = (Prestador){0}; // Retorna un prestador vacio si no se encuentra
    }
    return prestador;
}

void mostrarLista(LVO lista)
{
    if (lista.head == NULL)
    {
        printf("La lista esta vacia\n");
    }
    else
    {
        NodoLista *actual = lista.head;
        while (actual != NULL)
        {
            mostrarPrestador(actual->prestador);
            actual = actual->siguiente;
        }
    }
}
void liberarLista(LVO *lista)
{
    NodoLista *actual = lista->head;
    while (actual != NULL)
    {
        NodoLista *temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
    lista->head = NULL;
    lista->size = 0;
}

int memorizacionPrevia(LVO *lista)
{

    FILE *fp;
    Prestador aux;
    int returnAlta;

    if ((fp = fopen("Prestadores.txt", "r")) == NULL)
    {
        return 3; // no se pudo abrir el archivo
    }

    fseek(fp, 0, SEEK_END); //(fichero, desplazamiento, origen) , SEEK_END el desplazamiento se cuenta desde el final del archivo

    if (ftell(fp) == 0) // indica la posicion actual en un archivo
    {
        return 2;
    }

    rewind(fp);
    while (!(feof(fp)))
    {

        fscanf(fp, "%d\n", &aux.dni);

        if (aux.dni < MINDNI || aux.dni > INFINITO)
        {
            printf("El prestador asociado al DNI %d no pudo ser cargado (DNI invalido).\n", aux.dni);

            for (int i = 0; i < 5; i++)
            {
                fscanf(fp, "%*[^\n]\n");
                if (feof(fp))
                {
                    break; // Salir del bucle si llegamos al final del archivo
                }
            }
        }

        fscanf(fp, "%[^\n]\n", aux.nombre);
        fscanf(fp, "%[^\n]\n", aux.servicios);
        fscanf(fp, "%[^\n]\n", aux.domicilio);
        fscanf(fp, "%[^\n]\n", aux.email);
        fscanf(fp, "%[^\n]\n", aux.telefono);

        returnAlta = altaLVOMem(aux, lista);

        if (!returnAlta)
        {
            printf("Ya existe un prestador asociado al dni %d en la estructura.\n", aux.dni);
        }
    }
    fclose(fp);
    return 1; // Memorizacion exitosa
}