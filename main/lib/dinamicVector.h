#ifndef _DINAMICSTRUCTURE
#define _DINAMICSTRUCTURE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Firmas de funciones
struct vector;

typedef struct vector
{
    size_t tam;
    void** dato;
}vector_t;

//crea el vector
vector_t* vector_new(size_t tam_inicial);

//inserta un elemento en la posicion especifica
//devuelve un bool si hubo un error o no
bool vector_insert(vector_t* vector, size_t indice, void* elemento);

//devuelve el valor del elemento segun el indice 
void* vector_get(vector_t* vector, size_t indice);

//obtiene el tamaño del vector
size_t vector_length(vector_t* vector);

//redimensiona el vector a un nuevo tamaño mas grande 
bool vector_resize(vector_t* vector, size_t tam);

//destruye el vector de la memoria
void vector_destroy(vector_t* vector);

#endif