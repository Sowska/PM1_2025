#ifndef PRESTADOR_H
#define PRESTADOR_H

typedef struct {
    int dni;
    char nombre[50];
    char servicios[50];
    char domicilio[100];
    char email[100];
    char telefono[20];
} Prestador;
int sonDiferentes(Prestador p1, Prestador p2);
void mostrarPrestador(Prestador p);
void limpiarPantalla();
void modificar_nombre(Prestador* p);
void modificar_servicio(Prestador* p);
void modificar_domicilio(Prestador* p);
void modificar_email(Prestador* p);
void modificar_telefono(Prestador* p);

#endif