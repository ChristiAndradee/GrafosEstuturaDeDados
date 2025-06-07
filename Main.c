#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define V 10

// Terminais de Curitiba
const char *terminais[V] = {
    "Boqueirao", "CIC", "Pinheirinho", "Cabral", "Guadalupe",
    "Capao Raso", "Santa Candida", "Fazendinha", "Campo Comprido", "Hauer"
};

// Matriz de tempo entre terminais
int tempo[V][V] = {
    {0, 10, 15, 0, 0, 20, 0, 0, 0, 25}, //Boqueirao
    {10, 0, 5, 0, 0, 15, 0, 10, 0, 0}, //CIC
    {15, 5, 0, 0, 0, 5, 0, 0, 20, 0}, //Pinheirinho
    {0, 0, 0, 0, 10, 0, 5, 0, 0, 0}, //Cabral
    {0, 0, 0, 10, 0, 0, 0, 0, 0, 5}, //Guadalupe
    {20, 15, 5, 0, 0, 0, 0, 10, 0, 0}, //Capao Raso
    {0, 0, 0, 5, 0, 0, 0, 15, 0, 0}, //Santa Candida
    {0, 10, 0, 0, 0, 10, 15, 0, 10, 0}, //Fazendinha
    {0, 0, 20, 0, 0, 0, 0, 10, 0, 5}, // Campo Comprido
    {25, 0, 0, 0, 5, 0, 0, 0, 5, 0} // Hauer
};

void menu() {
    int escolha, origem, destino;
    do {
        printf("\n============================\n");
        printf("     MENU DE OPCOES\n");
        printf("============================\n");
        printf("1. Buscar menor tempo entre dois terminais\n");
        printf("2. Buscar com menos baldeacoes\n");
        printf("3. Melhor rota para visitar todos os terminais\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                break;

            case 2:
                break;

            case 3:
                melhor_rota_todos_terminais();
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);
}

void melhor_rota_todos_terminais() {
    bool visitado[V] = {false};
    int atual = 0;
    int rota[V], tempo_total = 0;
    rota[0] = atual;
    visitado[atual] = true;

    for (int i = 1; i < V; i++) {
        int menor_tempo = INT_MAX;
        int proximo = -1;

        for (int j = 0; j < V; j++) {
            if (!visitado[j] && tempo[atual][j] > 0 && tempo[atual][j] < menor_tempo) {
                menor_tempo = tempo[atual][j];
                proximo = j;
            }
        }

        if (proximo != -1) {
            rota[i] = proximo;
            tempo_total += menor_tempo;
            visitado[proximo] = true;
            atual = proximo;
        }
    }

    printf("\n[Melhor Caminho para Visitar Todos os Terminais - Aprox. Vizinho Mais Proximo]:\n");
    for (int i = 0; i < V; i++) {
        printf("%s", terminais[rota[i]]);
        if (i != V - 1) printf(" -> ");
    }
    printf("\nTempo total estimado: %d minutos\n", tempo_total);
}

int main() {
    menu();
    return 0;
}