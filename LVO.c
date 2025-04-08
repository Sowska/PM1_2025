#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10
#define MINDNI 10000000
#define INFINITO 99999999

typedef struct {
    int exito;
    int lugar;
} resultLoc;
typedef struct {
    int dni;
    char nombre[80];
    char servicios[120];
    char domicilio[80];
    char email[50];
    char telefono[30];
} Prestador;

    typedef struct NodoLista {
        Prestador prestador;
        struct NodoLista* siguiente;
    } NodoLista;
    
    typedef struct {
        NodoLista* head;          
        int size;    
    } LVO;

    void inicializarLista(LVO* lista) {
        lista->head = NULL;  // La lista comienza vacia
        lista->size = 0;     // Tamaño inicial es 0
    }
    
    resultLoc localizarLVO(LVO lista, int dni) {
        resultLoc loc;
        loc.lugar = 0;
        loc.exito = 0;

        if (lista.head == NULL) {  // Lista vacia

            return loc;
        }

        NodoLista* actual = lista.head;
        int index = 0;

        while (actual != NULL && actual->prestador.dni != dni) {
            actual = actual->siguiente;
            index++;
        }

        loc.exito = actual != NULL;
        loc.lugar = index; 
        return loc;
    }

    int altaLVO(Prestador prestador, LVO* lista) {
        if (lista->size == MAX) {
            return 2; // Lista llena
        }

        resultLoc aux = localizarLVO(*lista, prestador.dni);
        if (aux.exito) {
            return 0; // El elemento ya existe
        }

        NodoLista* nuevoNodo = (NodoLista*)malloc(sizeof(NodoLista));
        if (!nuevoNodo) {
            return 3; // Memoria insuficiente
        }
        
        nuevoNodo->prestador = prestador;
        nuevoNodo->siguiente = NULL;

        if (lista->head == NULL || lista->head->prestador.dni > prestador.dni) {
            nuevoNodo->siguiente = lista->head;
            lista->head = nuevoNodo;
        } else {
            NodoLista* actual = lista->head;
            while (actual->siguiente != NULL && actual->siguiente->prestador.dni < prestador.dni) {
                actual = actual->siguiente;
            }
            nuevoNodo->siguiente = actual->siguiente;
            actual->siguiente = nuevoNodo;
        }

        lista->size++;
        return 1; // Alta exitosa
    }
    int bajaLVO(Prestador prestador, LVO* lista) {
        if (lista->head == NULL) {
            return 2; // Lista vacia
        }

        resultLoc aux = localizarLVO(*lista, prestador.dni);
        if (!aux.exito) {
            return 0; // El elemento no existe
        }

        NodoLista* actual = lista->head;
        NodoLista* anterior = NULL;

        while (actual != NULL && actual->prestador.dni != prestador.dni) {
            anterior = actual;
            actual = actual->siguiente;
        }

        if (anterior == NULL) { // El nodo a eliminar es el primero
            lista->head = actual->siguiente;
        } else {
            anterior->siguiente = actual->siguiente;
        }

        free(actual);
        lista->size--;
        return 1; // Baja exitosa
    }
    int modificarLVO(Prestador prestador, LVO* lista) {
        if (lista->head == NULL) {
            return 2; // Lista vacia
        }

        resultLoc aux = localizarLVO(*lista, prestador.dni);
        if (!aux.exito) {
            return 0; // El elemento no existe
        }

        NodoLista* actual = lista->head;
        int index = 0;

        while (actual != NULL && index < aux.lugar) {
            actual = actual->siguiente;
            index++;
        }

        if (actual != NULL) {
            actual->prestador = prestador;
            return 1;
        }
        
        return 0;
    }
    Prestador evocarLVO(LVO lista, int dni) {
        Prestador prestador;
        resultLoc aux = localizarLVO(lista, dni);
        if (aux.exito) {
            prestador = lista.head->prestador;
        } else {
            prestador = (Prestador){0, "", "", "", "", ""}; 
        }
        return prestador;
    }
    void mostrarPrestador(Prestador p) {
        printf("\nDNI: %d\n Nombre: %s\n Servicios: %s\n Domicilio: %s\n Email: %s\n Telefono: %s\n",
               p.dni, p.nombre, p.servicios, p.domicilio, p.email, p.telefono);
    }
    void mostrarLista(LVO lista) {
        NodoLista* actual = lista.head;
        while (actual != NULL) {
            mostrarPrestador(actual->prestador);
            actual = actual->siguiente;
        }
    }
    void liberarLista(LVO* lista) {
        NodoLista* actual = lista->head;
        while (actual != NULL) {
            NodoLista* temp = actual;
            actual = actual->siguiente;
            free(temp);
        }
        lista->head = NULL;
        lista->size = 0;
    }

int main(int argc, char const *argv[])
{
    LVO lista;
    inicializarLista(&lista);
    Prestador p1 = {26798818, "Julio Argentino Roca", "Mecánico", "Bulevar Olivera 11556", "26798818@server.com", "111-222-333"};
    Prestador p2 = {30876543, "José de San Martín", "Electricista", "Avenida Libertador 3500", "30876543@server.com", "222-333-444"};
    Prestador p3 = {31234567, "Manuel Belgrano", "Plomero", "Calle Belgrano 765", "31234567@server.com", "333-444-555"};
    Prestador p4 = {27543219, "Juan Domingo Perón", "Gasista", "Diagonal Perón 1945", "27543219@server.com", "444-555-666"};
    Prestador p5 = {29876543, "Eva Duarte", "Carpintero", "Calle Evita 123", "29876543@server.com", "555-666-777"};
    int resultA=0,resultB=0;
    resultA= altaLVO(p1, &lista);
    resultA= altaLVO(p2, &lista);
    resultA= altaLVO(p3, &lista);  
    resultA= altaLVO(p4, &lista);
    resultA= altaLVO(p5, &lista);

    printf("Resultado ALTA : %d\n ",resultA);
    printf("Los prestadores son : \n"); 
    mostrarLista(lista);

    resultB= bajaLVO(p3, &lista);
    printf("Resultado BAJA : %d\n ",resultB);
   resultLoc result = localizarLVO(lista, 31234567);
    printf("La busqueda retorno como exito %d en el lugar %d\n", result.exito, result.lugar);

    return 0;
