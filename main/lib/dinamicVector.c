
#include "dinamicVector.h"
#include "freertos/FreeRTOS.h"

vector_t *vector_new(size_t tam_inicial)
{

    //creamos la estructura y pedimos memoria para la estructura
    vector_t *vector = malloc(sizeof(vector_t));
    if (vector == NULL)
        return NULL;
    //seteamos el tamaño inicial del vector
    vector->tam = tam_inicial;

    //pedimos espacio para n datos de void genericos
    vector->dato = malloc(sizeof(void *) * tam_inicial);
    if (vector->dato == NULL)
    {
        free(vector);
        return NULL;
    }
    //Limpiamos el vector
    for (size_t i = 0; i < tam_inicial; i++)
    {
        vector->dato[i] = NULL;
    }
    return vector;
}
//inserta un elemento en la posicion especifica
bool vector_insert(vector_t *vector, size_t indice, void *elemento)
{ //valida el indice de inssersion
    if (indice < 0 || indice >= vector->tam)
        return false;
    //asigna el valir al indice
    vector->dato[indice] = elemento;
    return true;
}
//devuelve el valor del elemento segun el indice
void *vector_get(vector_t *vector, size_t indice)
{
    if (indice < 0 || indice >= vector->tam)
        return NULL;
    return vector->dato[indice];
}

//obtiene el tamaño del vector
size_t vector_length(vector_t *vector)
{
    return vector->tam;
}

//redimensiona el vector a un nuevo tamaño mas grande
bool vector_resize(vector_t *vector, size_t tam)
{ //valida un tamaño mayor al actual
    if (tam < vector->tam)
        return false;

    printf("PAss 1?\n");

    //copia los datos del vector a un void** al tamaño pedido
    void **datos_nuevos = realloc(vector->dato, tam * sizeof(void *));
    if (datos_nuevos == NULL)
        return false;

    printf("PAss 2?\n");
    free(vector->dato); //libera los datos del viejo vector
    printf("PAss 3?\n");
    vector->dato = datos_nuevos; // asigna el nuevo void** al vector dinamico
    printf("PAss 4?\n");
    vector->tam = tam; // nuevo tamaño asignado
    printf("PAss 5?\n");
    return true;
}

//destruye el vector de la memoria
void vector_destroy(vector_t *vector)
{
    free(vector->dato);
    free(vector);
}
