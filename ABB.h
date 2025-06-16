#ifndef ABB_H
#define ABB_H
#include "Prestador.h"
#include "NodoPila.h"

typedef struct
{
    NodoArbol *raiz;
    NodoArbol *pos;
    NodoArbol *padre;
} Arbol;

typedef struct Nodo
{
    Prestador prestador;
    struct Nodo *izq;
    struct Nodo *der;
} Nodo;

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

    if (arbol->raiz == NULL)
    {

        return 0;
    }

    arbol->pos = arbol->raiz;
    arbol->padre = arbol->raiz;

    while (arbol->pos != NULL && dni != arbol->pos->prestador.dni)
    {
        (*costo)++;

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
    }

    if (arbol->pos != NULL)
    {
        (*costo)++;
    }
    return (arbol->pos != NULL);
}

int altaABB(Arbol *arbol, Prestador x, float *costo)
{
    float costoloc = 0;

    if (localizarABB(arbol, x.dni, &costoloc))
    {
        return 0;
    }
    else
    {
        NodoArbol *nuevo = (NodoArbol *)malloc(sizeof(NodoArbol));
        if (nuevo == NULL)
        {
            return 2; // Memoria insuficiente
        }
        if (arbol->raiz == NULL)
        {
            arbol->raiz = nuevo;
            arbol->padre = nuevo;
            *costo += .5;
        }
        else
        {
            if (x.dni > arbol->padre->prestador.dni)
            {
                arbol->padre->der = nuevo;
            }
            else
            {
                arbol->padre->izq = nuevo;
            }
            *costo += 0.5;
        }

        return 1;
    }
}

int bajaABB(Prestador prestador, Arbol *arbol, int flag, float *costo)
{
    NodoArbol *auxi, *elem;
    float costoloc = 0.0;
    int opcion = 0;

    if (arbol->raiz == NULL)
        return 2;

    if (!localizarABB(arbol, prestador.dni, &costoloc))
        return 0; // Elemento no existe

    if (flag == 1) // Baja con confirmacion
    {
        do
        {
            printf("El prestador a eliminar es:\n");
            mostrarPrestador(arbol->pos->prestador);
            printf("¿Está seguro que desea eliminarlo?\n");
            printf("1. Sí\n");
            printf("2. No\n");
            printf("Seleccione una opción: ");
            scanf("%d", &opcion);
            getchar(); // limpiar buffer
        } while (opcion != 1 && opcion != 2);

        if (opcion == 2)
            return 3; // Baja cancelada por el usuario
    }
    else
    {
        if (sonDiferentes(arbol->pos->prestador, prestador))
            return 3; // Prestador diferente
    }

    // Nodo hoja
    if (arbol->pos->der == NULL && arbol->pos->izq == NULL)
    {
        if (arbol->pos == arbol->raiz)
        {
            arbol->raiz = NULL;
        }
        else if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
        {
            arbol->padre->izq = NULL;
        }
        else
        {
            arbol->padre->der = NULL;
        }
        *costo += 0.5;
        free(arbol->pos);
        arbol->pos = NULL;
        return 1;
    }
    // Nodo con un hijo
    if (arbol->pos->der == NULL || arbol->pos->izq == NULL)
    {
        auxi = (arbol->pos->izq != NULL) ? arbol->pos->izq : arbol->pos->der;
        if (arbol->pos == arbol->raiz)
        {
            arbol->raiz = auxi;
        }
        else if (arbol->pos->prestador.dni < arbol->padre->prestador.dni)
        {
            arbol->padre->izq = auxi;
        }
        else
        {
            arbol->padre->der = auxi;
        }
        *costo += 0.5;
        free(arbol->pos);
        arbol->pos = NULL;
        return 1;
    }
    // Nodo con dos hijos

    elem = arbol->pos->der;
    arbol->padre = arbol->pos;
    NodoArbol *ant_aux = NULL;
    while (elem->izq != NULL)
    {
        ant_aux = elem;
        elem = elem->izq;
    }
    arbol->pos->prestador = elem->prestador;
    *costo += 1.0;
    if (ant_aux == NULL)
    {
        arbol->pos->der = elem->der;
    }
    else
    {
        ant_aux->izq = elem->der;
    }
    *costo += 0.5;
    free(elem);
    elem = NULL;
    return 1;
}

Prestador evocarABB(Arbol *arbol, int x, float *costo)
{
    (*costo) = 0;
    Prestador p;

    int result = localizarABB(arbol, x, costo);

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
        printf("El árbol está vacío.\n");
        return;
    }

    NodoPila *pila = NULL;
    push(&pila, raiz);
    int contador = 0;

    while (!pilaVacia(pila))
    {
        NodoArbol *actual = pop(&pila);

        mostrarPrestador(actual->prestador);

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

        printf("\n\t*-*-*-*-*-*-*-*-*-*-*\n");

        contador++;

        if (contador % 10 == 0)
        {
            printf("Presiona Enter para continuar...\n");
            getchar();
            limpiarPantalla();
        }

        // empujamos hijo derecho y izquierdo
        if (actual->der != NULL)
        {
            push(&pila, actual->der);
        }

        if (actual->izq != NULL)
        {
            push(&pila, actual->izq);
        }
    }

    printf("\n** FIN DEL ÁRBOL **\n");
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
    float costoOcioso = 0;

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

        returnAlta = altaABB(arbol, aux, &costoOcioso);
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
    float costoOcioso = 0.0;

    int resultado = localizarABB(arbol, dni, &costoOcioso);

    if (resultado)
    {
        printf("El prestador encontrado es:\n");

        mostrarPrestador(arbol->pos->prestador);
        do
        {
            printf("\n Que campo del prestador usted desea modificar?\n\n");
            printf("1-Nombre\n2-Servicio\n3-Domicilio\n4-Email\n5-Telefono\n");
            printf("Si desea modificar todos los campos, ingrese 6 \n");
            printf("Para regresar, ingrese 7 \n");
            scanf("%d", &opmod);
        } while (opmod < 0 || opmod > 7);
        getchar();
        switch (opmod)
        {
        case 1:
            printf("Ingrese el nuevo nombre: ");
            scanf(" %[^\n]", arbol->pos->prestador.nombre);
            printf("Modificación exitosa.\n");
            getchar();
            break;
        case 2:
            printf("Ingrese el nuevo servicio: ");
            scanf(" %[^\n]", arbol->pos->prestador.servicios);
            getchar();
            break;
        case 3:
            printf("Ingrese el nuevo domicilio: ");
            scanf(" %[^\n]", arbol->pos->prestador.domicilio);
            printf("Modificación exitosa.\n");
            getchar();
            break;
        case 4:
            printf("Ingrese el nuevo email: ");
            scanf(" %[^\n]", arbol->pos->prestador.email);
            printf("Modificación exitosa.\n");
            getchar();
            break;
        case 5:
            printf("Ingrese el nuevo telefono: ");
            scanf(" %[^\n]", arbol->pos->prestador.telefono);
            printf("Modificación exitosa.\n");
            getchar();
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
            getchar();
            break;

        case 7:
            printf("Volviendo...\n");
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

#endif
