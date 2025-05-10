#include <iostream>
#include <string.h>

struct Pelicula {
    char nombre[50];
    int year;
    char genero;
    float dineroRecaudado;
    struct Pelicula *left;
    struct Pelicula *right;
};

struct Pelicula *raiz = NULL;

struct Pelicula* crearNodo() {
    struct Pelicula 
}


