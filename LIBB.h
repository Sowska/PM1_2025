#ifndef LIBB_H
#define LIBB_H
#include "Prestador.h"
#include "Resultloc.h"

typedef struct
{
    Prestador *prestadores[MAX];
    int ultimo;
} LIBB;

resultLoc localizarLIBB(LIBB lista, int dni, float *costo)
{
    resultLoc loc;
    (*costo) = 0.0;
    int li = 0, ls = lista.ultimo, t;
    loc.exito = 0;

    if (lista.ultimo == -1)
    {
        loc.lugar = 0;
        return loc;
    }

    int controlTestigo[lista.ultimo + 1];
    for (int i = 0; i <= lista.ultimo; i++)
    {
        controlTestigo[i] = 0;
    }

    while (li < ls)
    {
        t = (li + (ls + 1)) / 2;
        if (lista.prestadores[t]->dni <= dni)
        {
            li = t;
            if (controlTestigo[t] == 0)
            {
                (*costo) += 2;
                controlTestigo[t] = 1;
            }
        }
        else
        {
            ls = t - 1;
            (*costo) += 2;
        }
    }

    if (controlTestigo[li] == 0)
    {
        (*costo) += 2;
        controlTestigo[li] = 1;
    }

    if (lista.prestadores[li]->dni == dni)
    {
        loc.exito = 1;
        loc.lugar = li;
        return loc;
    }

    loc.lugar = (lista.prestadores[li]->dni < dni) ? li + 1 : li;
    return loc;
}

int altaLIBB(Prestador prestador, LIBB *lista, float *costo)
{
    (*costo) = 0;
    float costonull = 0;
    if (lista->ultimo == MAX - 1)
    {
        return 2; // Lista llena
    }
    resultLoc aux = localizarLIBB(*lista, prestador.dni, &costonull);
    if (aux.exito)
    {
        return 0; // El elemento ya existe
    }
    Prestador *newprestador = (Prestador *)malloc(sizeof(Prestador));
    if (!newprestador)
    {
        return 3; // Memoria insuficiente
    }
    *newprestador = prestador;

    for (int i = lista->ultimo; i >= aux.lugar; i--)
    {
        lista->prestadores[i + 1] = lista->prestadores[i];
        (*costo) += 0.5;
    }
    lista->prestadores[aux.lugar] = newprestador;
    lista->ultimo++;
    return 1;
}

int bajaLIBB(Prestador prestador, LIBB *libb, float *costo, int flag)
{
    (*costo) = 0.0;
    float costoloc = 0;
    int opcion = 0;

    if (libb->ultimo == -1)
    {
        return 2; // Lista vacía
    }

    resultLoc aux = localizarLIBB(*libb, prestador.dni, &costoloc);
    if (!aux.exito)
    {
        return 0; // El elemento no existe
    }

    if (flag == 1) // baja con confirmacion
    {
        do
        {
            printf("El prestador encontrado es:\n");
            mostrarPrestador(*libb->prestadores[aux.lugar]);
            printf("¿Desea eliminarlo? (1: Si, 2: No): ");
            scanf("%d", &opcion);
            getchar();
        } while (opcion != 1 && opcion != 2);

          if (opcion != 1)
            return 3; // Baja cancelada
    } else    {
        if (sonDiferentes(*libb->prestadores[aux.lugar], prestador))
            return 3; // Prestador diferente
    }
    
    free(libb->prestadores[aux.lugar]);
    libb->prestadores[aux.lugar] = NULL;

    for (int i = aux.lugar; i < libb->ultimo; i++) {
        libb->prestadores[i] = libb->prestadores[i + 1];
        *costo += 0.5;
    }

    libb->ultimo--;

    return 1;
}

void modificarLIBB(int dni, LIBB *lista)
{

    int opmod = 0;

    float costoDespreciado = 0;

    if (lista->ultimo == -1)
    {
        printf("Lista vacia\n");
        return;
    }

    resultLoc aux = localizarLIBB(*lista, dni, &costoDespreciado);

    if (!aux.exito)
    {
        printf("El prestador no existe en la lista.\n");
        return;
    }

    printf("El prestador encontrado es:\n");
    mostrarPrestador(*lista->prestadores[aux.lugar]);

    do
    {
        printf("\n Que campo del prestador usted desea modificar?\n\n");
        printf("1-Nombre\n2-Servicio\n3-Domicilio\n4-Email\n5-Telefono\n");
        printf("Si desea modificar todos los campos, ingrese 6 \n");
        printf("Para cancelar la operación, presione 7 \n");
        scanf("%d", &opmod);
    } while (opmod < 0 || opmod > 7);
    getchar();

    switch (opmod)
    {

    case 1:

        printf("Usted selecciono: MODIFICAR NOMBRE\n\n");

        modificar_nombre(lista->prestadores[aux.lugar]);
        printf("¡Modificacion exitosa!\n\n");
        break;
    case 2:

        printf("Usted selecciono: MODIFICAR SERVICIO\n\n");
        modificar_servicio(lista->prestadores[aux.lugar]);
        printf("¡Modificacion exitosa!\n\n");
        break;
    case 3:

        printf("Usted selecciono: MODIFICAR DOMICILIO\n\n");
        modificar_domicilio(lista->prestadores[aux.lugar]);
        printf("¡Modificacion exitosa!\n\n");
        break;
    case 4:

        printf("Usted selecciono: MODIFICAR EMAIL\n\n");
        modificar_email(lista->prestadores[aux.lugar]);
        printf("¡Modificacion exitosa!\n\n");
        break;
    case 5:

        printf("Usted selecciono: MODIFICAR TELEFONO\n\n");
        modificar_telefono(lista->prestadores[aux.lugar]);
        printf("¡Modificacion exitosa!\n\n");
        break;
    case 6:

        printf("Usted selecciono: MODIFICAR TODOS LOS CAMPOS\n\n");

        modificar_nombre(lista->prestadores[aux.lugar]);
        modificar_servicio(lista->prestadores[aux.lugar]);
        modificar_domicilio(lista->prestadores[aux.lugar]);
        modificar_email(lista->prestadores[aux.lugar]);
        modificar_telefono(lista->prestadores[aux.lugar]);

        printf("¡Modificacion exitosa!\n\n");

        break;

    case 7:
        printf("Operación cancelada.\n");
        break;

    default:
        printf("Error inesperado\n");

        break;
    }
}

Prestador evocarLIBB(LIBB lista, int dni, float *costo)
{
    (*costo) = 0;

    Prestador prestador;
    resultLoc aux = localizarLIBB(lista, dni, costo);
    if (aux.exito)
    {
        prestador = *lista.prestadores[aux.lugar];
    }
    else
    {
        prestador = (Prestador){0, "", "", "", "", ""};
    }
    return prestador;
}

void mostrarLIBBPaginada(LIBB lista, int pagina, int elementosPorPagina)
{
    if (lista.ultimo == -1)
    {
        printf("Lista vacia\n");
        return;
    }

    int inicio = (pagina - 1) * elementosPorPagina;
    int fin = inicio + elementosPorPagina <= lista.ultimo + 1 ? inicio + elementosPorPagina : lista.ultimo + 1;

    printf("\nPRESTADORES EN SISTEMA \n");
    for (int i = inicio; i < fin; i++)
    {
        printf("\nDNI: %d\n Nombre: %s\n Servicios: %s\n Domicilio: %s\n Email: %s\n Telefono: %s\n\n*---------------------*\n\n",
               lista.prestadores[i]->dni,
               lista.prestadores[i]->nombre,
               lista.prestadores[i]->servicios,
               lista.prestadores[i]->domicilio,
               lista.prestadores[i]->email,
               lista.prestadores[i]->telefono);
    }
    if (fin == lista.ultimo)
    {
        printf("Fin de la lista\n");
    }
    else
    {
        printf("Pagina %d de %d\n\n", pagina, (lista.ultimo / elementosPorPagina) + 1);
    }
}

void initLIBB(LIBB *lista)
{
    lista->ultimo = -1;
    for (int i = 0; i < MAX; i++)
    {
        lista->prestadores[i] = NULL;
    }
}
void liberarLIBB(LIBB *lista)
{
    for (int i = 0; i <= lista->ultimo; i++)
    {
        free(lista->prestadores[i]);
    }
    lista->ultimo = -1;
}

int memorizacionPreviaLIBB(LIBB *lista)
{

    FILE *fp;
    Prestador aux;
    int returnAlta;
    int auxDNI = 0;
    float costoDespreciado = 0.0;

    if ((fp = fopen("Prestadores.txt", "r")) == NULL)
    {
        return 0;
    }

    fseek(fp, 0, SEEK_END); //(fichero, desplazamiento, origen) , SEEK_END el desplazamiento se cuenta desde el final del archivo
    if (ftell(fp) == 0)     // indica la posicion actual en un archivo
    {
        return 2;
    }

    rewind(fp);

    while (lista->ultimo < MAX - 1 && !(feof(fp)))
    {
        fscanf(fp, "%d\n", &auxDNI);

        if (auxDNI < MINDNI || auxDNI > INFINITO)
        {
            for (int i = 0; i < 5; i++)
            {
                fscanf(fp, "%*[^\n]\n");
                if (feof(fp))
                {
                    break; // Salir del bucle si llegamos al final del archivo
                }
            }
        }
        aux.dni = auxDNI;
        fscanf(fp, "%[^\n]\n", aux.nombre);
        fscanf(fp, "%[^\n]\n", aux.servicios);
        fscanf(fp, "%[^\n]\n", aux.domicilio);
        fscanf(fp, "%[^\n]\n", aux.email);
        fscanf(fp, "%[^\n]\n", aux.telefono);

        returnAlta = altaLIBB(aux, lista, &costoDespreciado);

        if (returnAlta == 0)

        {
            printf("Ya existe un prestador asociado al dni %d en la estructura.\n", aux.dni);
        }
    }
    fclose(fp);
    return (lista->ultimo == MAX - 1) ? 4 : 1;
}

#endif // LIBB_H