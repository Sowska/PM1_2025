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

#endif