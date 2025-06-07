#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 10

// Terminais de Curitiba
const char *terminais[V] = {
    "Boqueirão", "CIC", "Pinheirinho", "Cabral", "Guadalupe",
    "Capão Raso", "Santa Cândida", "Fazendinha", "Campo Comprido", "Hauer"
};

// Matriz de tempo entre terminais
int tempo[V][V] = {
    {0, 10, 15, 0, 0, 20, 0, 0, 0, 25},
    {10, 0, 5, 0, 0, 15, 0, 10, 0, 0},
    {15, 5, 0, 0, 0, 5, 0, 0, 20, 0},
    {0, 0, 0, 0, 10, 0, 5, 0, 0, 0},
    {0, 0, 0, 10, 0, 0, 0, 0, 0, 5},
    {20, 15, 5, 0, 0, 0, 0, 10, 0, 0},
    {0, 0, 0, 5, 0, 0, 0, 15, 0, 0},
    {0, 10, 0, 0, 0, 10, 15, 0, 10, 0},
    {0, 0, 20, 0, 0, 0, 0, 10, 0, 5},
    {25, 0, 0, 0, 5, 0, 0, 0, 5, 0}
};