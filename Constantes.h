#ifndef CONSTANTES_H
#define CONSTANTES_H

#define MAX 20
#define MINDNI 10
#define INFINITO 99

void limpiarPantalla()
{
#ifdef _WIN32
    system("cls"); // comando para Windows
#else
    system("clear"); // comando para Unix
#endif
} 

#endif