#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ABB.h"
#include "Prestador.h"
#include "Constantes.h"

typedef struct Nodo
{
    Prestador prestador;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

NodoArbol *crearNodo(Prestador prestador)
{
    Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo));
    if (nuevo != NULL)
    {
        nuevo->prestador = prestador;
        nuevo->izq = NULL;
        nuevo->der = NULL;
    }

    return nuevo;
}

void freeNodo(NodoArbol *nodo)
{
    if (nodo == NULL)
    {
        return;
    }
    freeNodo(nodo->izq);

    freeNodo(nodo->der);

    free(nodo);
}

void vaciarArbol(Arbol *arbol)
{
    if (arbol->raiz != NULL)
    {
        freeNodo(arbol->raiz);
        arbol->raiz = NULL;
    }
}

// localizar

int localizarABB(Arbol *arbol, int dni, float *costo)
{
    (*costo) = 0;

    if (arbol->raiz == NULL)
    {

        return 0;
    }

    arbol->pos = arbol->raiz;
    arbol->padre = arbol->raiz;

    while (arbol->pos != NULL && dni != arbol->pos->prestador.dni)
    {
        *costo = *costo + 1;

        if (arbol->pos->prestador.dni < dni)
        {
            arbol->padre = arbol->pos;
            arbol->pos = arbol->pos->der;
        }
        else
        {
            arbol->padre = arbol->pos;
            arbol->pos = arbol->pos->izq;
        }
        (*costo)++;
    }

    if (arbol->pos != NULL)
    {
        (*costo)++;
    }
    return (arbol->pos != NULL);
}

int altaABB(Arbol *arbol, Prestador x, float *costo)
{

    (*costo) = 0.0;

    if (localizarABB(arbol, x.dni, costo))
    {
        return 0;
    }
    else
    {
        NodoArbol *nuevoNodo = crearNodo(x);
        if (arbol->raiz == NULL)
        {
            arbol->raiz = nuevoNodo;
            arbol->padre = nuevoNodo;
            (*costo) += 0.5;
        }
        else
        {
            if (x.dni > arbol->padre->prestador.dni)
            {
                arbol->padre->der = nuevoNodo;
            }
            else
            {
                arbol->padre->izq = nuevoNodo;
            }
            (*costo) += 0.5;
        }

        return 1;
    }
}

int altaABBMem(Arbol *arbol, Prestador x)
{

    int costo = 0;

    if (localizarABB(arbol, x.dni, costo))
    {
        return 0;
    }
    else
    {
        NodoArbol *nuevoNodo = crearNodo(x);
        if (arbol->raiz == NULL)
        {
            arbol->raiz = nuevoNodo;
            arbol->padre = nuevoNodo;
        }
        else
        {
            if (x.dni > arbol->padre->prestador.dni)
            {
                arbol->padre->der = nuevoNodo;
            }
            else
            {
                arbol->padre->izq = nuevoNodo;
            }
        }

        return 1;
    }
}

int bajaABBConfirmada(int dni, Arbol *arbol)
{

    NodoArbol *auxi, *elem;
    int costoloc = 0;
    int opcion = 0;
    if (arbol->raiz == NULL)
    {
        return 2; // Arbol vacio
    }
    if (!localizarABB(arbol, dni, &costoloc))
    {
        return 0; // El elemento no existe
    }
    do
    {
        printf("El prestador a eliminar es:\n");
        imprimirPrestador(arbol->pos->prestador);
        printf("¿Esta seguro que desea eliminarlo?\n");
        printf("1. Si\n");
        printf("2. No\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

    } while (opcion != 1 && opcion != 2);

    switch (opcion)
    {
    case 1:
        // Caso 1: Nodo hoja - sin hijos
        if (arbol->pos->der == NULL && arbol->pos->izq == NULL)
        {
            if (arbol->pos == arbol->raiz)
            {
                arbol->raiz = NULL;
                free(arbol->pos);
                arbol->pos = NULL;
            }
            else
            {
                if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
                {
                    arbol->padre->izq = NULL;
                }
                else
                {
                    arbol->padre->der = NULL;
                }
                free(arbol->pos);
                arbol->pos = NULL;
            }
        }
        // Caso 2: Nodo con un solo hijo
        else if (arbol->pos->der == NULL || arbol->pos->izq == NULL)
        {
            auxi = (arbol->pos->izq != NULL) ? arbol->pos->izq : arbol->pos->der;
            if (arbol->pos == arbol->raiz)
            {
                arbol->raiz = auxi;
            }
            else
            {
                if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
                {
                    arbol->padre->izq = auxi;
                }
                else
                {
                    arbol->padre->der = auxi;
                }
            }
            free(arbol->pos);
            arbol->pos = NULL;
        }
        // Caso 3: Nodo con dos hijos
        else
        {
            elem = arbol->pos->der;
            arbol->padre = arbol->pos;
            NodoArbol *ant_aux = NULL;

            while (elem->izq != NULL) // Esto busca el minimo del subarbol derecho (nueva politica de reemplazo).
            {
                ant_aux = elem;
                elem = elem->izq;
            }
            arbol->pos->prestador = elem->prestador;

            if (ant_aux == NULL)
            {

                // El hijo derecho es el minimo entonces
                arbol->pos->der = elem->der;
            }
            else
            {
                // El minimo tiene hijo derecho
                ant_aux->izq = elem->der;
            }

            free(elem);
            elem = NULL;
        }
        return 1;

        break;

    case 2:

        return 3;

        break;

    default:

        printf("Error inesperado en la baja\n");
        break;
    }
}

int bajaABBAutomatica(Arbol *arbol, Prestador x, float *costo)
{
    NodoArbol *auxi, *elem;
    (*costo) = 0.0;
    int costoloc = 0;

    if (arbol->raiz == NULL)
    {
        return 2;
    }

    if (!localizarABB(arbol, x.dni, &costoloc))
    {
        return 0;
    }
    else
    {
        if (sonDiferentes(arbol->pos->prestador, x))
        {
            return 3;
        }

        // Caso 1: Nodo hoja - sin hijos
        if (arbol->pos->der == NULL && arbol->pos->izq == NULL)
        {
            if (arbol->pos == arbol->raiz)
            {
                arbol->raiz = NULL;
                (*costo) += 0.5;
                free(arbol->pos);
                arbol->pos = NULL;
            }
            else
            {
                if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
                {
                    arbol->padre->izq = NULL;
                }
                else
                {
                    arbol->padre->der = NULL;
                }
                (*costo) += 0.5;
                free(arbol->pos);
                arbol->pos = NULL;
            }
        }
        // Caso 2: Nodo con un solo hijo
        else if (arbol->pos->der == NULL || arbol->pos->izq == NULL)
        {
            auxi = (arbol->pos->izq != NULL) ? arbol->pos->izq : arbol->pos->der;
            if (arbol->pos == arbol->raiz)
            {
                arbol->raiz = auxi;
            }
            else
            {
                if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
                {
                    arbol->padre->izq = auxi;
                }
                else
                {
                    arbol->padre->der = auxi;
                }
                (*costo) += 0.5;
            }
            free(arbol->pos);
            arbol->pos = NULL;
        }
        // Caso 3: Nodo con dos hijos
        else
        {
            elem = arbol->pos->der;
            arbol->padre = arbol->pos;
            NodoArbol *ant_aux = NULL;

            while (elem->izq != NULL) // Esto busca el minimo del subarbol derecho (nueva politica de reemplazo).
            {
                ant_aux = elem;
                elem = elem->izq;
            }
            arbol->pos->prestador = elem->prestador;
            (*costo) += 0.5;

            if (ant_aux == NULL)
            {

                // El hijo derecho es el minimo entonces
                arbol->pos->der = elem->der;
            }
            else
            {
                // El minimo tiene hijo derecho
                ant_aux->izq = elem->der;
            }

            (*costo) += 0.5;
            free(elem);
            elem = NULL;
        }

        return 1;
    }
}

Prestador evocarABB(Arbol *arbol, int x, float *costo)
{
    (*costo) = 0.0;
    int costoloc = 0;
    Prestador p;

    int result = localizarABB(arbol, x, &costoloc);

    if (result)
    {
        p = arbol->pos->prestador;
    }
    else
    {
        p = (Prestador){0, "", "", "", "", ""};
    }

    return p;
}

void mostrarEstructuraABB(NodoArbol *raiz)
{
    if (raiz == NULL)
    {
        printf("El arbol está vacío.\n");
    }

    NodoArbol *stack[MAX];
    int top = -1;
    stack[++top] = raiz;
    int contador = 0;

    while (top >= 0)
    {
        NodoArbol *actual = stack[top--];

        imprimirPrestador(actual->prestador);

        if (actual->izq != NULL)
        {
            printf("DNI del nodo izquierdo: %d\n", actual->izq->prestador.dni);
        }
        else
        {
            printf("Nodo izquierdo: NULL\n");
        }

        if (actual->der != NULL)
        {
            printf("DNI del nodo derecho: %d\n", actual->der->prestador.dni);
        }
        else
        {
            printf("Nodo derecho: NULL\n");
        }

        printf("\n\t*-*-*-*-*-**-*-*-*-*-*\n");

        contador++;

        if (contador % 10 == 0)
        {
            printf("Presiona Enter para continuar...\n");
            getchar();
            limpiarPantalla();
        }

        if (actual->der != NULL)
        {
            stack[++top] = actual->der;
        }

        if (actual->izq != NULL)
        {
            stack[++top] = actual->izq;
        }
    }

    printf("\n** FIN DE LA LISTA **\n");
}

void initArbol(Arbol *arbol)
{
    arbol->raiz = NULL;
    arbol->pos = NULL;
    arbol->padre = NULL;
}

int memorizacionPreviaABB(Arbol *arbol)
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

        returnAlta = altaABBMem(arbol, aux);
        if (returnAlta == 0)
        {
            printf("Ya existe un prestador asociado al dni %d en la estructura.\n", aux.dni);
        }
    }

    fclose(fp);
    return 1;
}

void modificarABB(int dni, Arbol *arbol)
{
    int opmod = 0;

    int resultado = localizarABB(arbol, dni, NULL);

    if (resultado)
    {
        printf("El prestador encontrado es:\n");

        mostrarPrestador(arbol->pos->prestador);
        do
        {
            printf("\n Que campo del prestador usted desea modificar?\n\n");
            printf("1-Nombre\n2-Servicio\n3-Domicilio\n4-Email\n5-Telefono\n");
            printf("Si desea modificar todos los campos, ingrese 6 \n");
            scanf("%d", &opmod);
        } while (opmod < 0 || opmod > 6);

        switch (opmod)
        {
        case 1:
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\n]", arbol->pos->prestador.nombre);
            printf("Modificación exitosa.\n");
            break;
        case 2:
            printf("Ingrese el nuevo servicio: ");
            scanf(" %[^\n]", arbol->pos->prestador.servicios);
            break;
        case 3:
            printf("Ingrese el nuevo domicilio: ");
            scanf(" %[^\n]", arbol->pos->prestador.domicilio);
            printf("Modificación exitosa.\n");
            break;
        case 4:
            printf("Ingrese el nuevo email: ");
            scanf(" %[^\n]", arbol->pos->prestador.email);
            printf("Modificación exitosa.\n");
            break;
        case 5:
            printf("Ingrese el nuevo telefono: ");
            scanf(" %[^\n]", arbol->pos->prestador.telefono);
            printf("Modificación exitosa.\n");
            break;
        case 6:
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\n]", arbol->pos->prestador.nombre);
            printf("Ingrese el nuevo servicio: ");
            scanf(" %[^\n]", arbol->pos->prestador.servicios);
            printf("Ingrese el nuevo domicilio: ");
            scanf(" %[^\n]", arbol->pos->prestador.domicilio);
            printf("Ingrese el nuevo email: ");
            scanf(" %[^\n]", arbol->pos->prestador.email);
            printf("Ingrese el nuevo telefono: ");
            scanf(" %[^\n]", arbol->pos->prestador.telefono);
            printf("Modificación exitosa.\n");
            break;

        default:
            printf("Error inesperado\n");
            break;
        }
    }
    else
    {
        printf("El prestador no fue encontrado\n");
    }
}