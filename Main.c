#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define NUM_MAXIMO_TERMINAIS 10
#define TEMPO_MAXIMO 9999

const char *terminais[NUM_MAXIMO_TERMINAIS] = {
    "Boqueirao", "CIC", "Pinheirinho", "Cabral", "Guadalupe",
    "Capao Raso", "Santa Candida", "Fazendinha", "Campo Comprido", "Hauer"
};

int tempo[NUM_MAXIMO_TERMINAIS][NUM_MAXIMO_TERMINAIS] = {
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

void menu();
void melhor_rota_menos_tempo(int terminal_origem, int terminal_destino);
void melhor_rota_todos_terminais();
void listar_terminais();

int main() {
    menu();
    return 0;
}

void listar_terminais() {
    printf("\nTerminais disponíveis:\n");
    for (int i = 0; i < NUM_MAXIMO_TERMINAIS; i++) {
        printf("%d. %s\n", i, terminais[i]);
    }
}

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
                listar_terminais();
                printf("\nDigite o número do terminal de origem: ");
                scanf("%d", &origem);
                printf("Digite o número do terminal de destino: ");
                scanf("%d", &destino);
                melhor_rota_menos_tempo(origem, destino);
               
                break;

            case 2:
                listar_terminais();
                printf("\nDigite o número do terminal de origem: ");
                scanf("%d", &origem);
                printf("Digite o número do terminal de destino: ");
                scanf("%d", &destino);
                melhor_rota_menos_baldeacoes(origem, destino);
               
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

void melhor_rota_menos_tempo(int terminal_origem, int terminal_destino) {
    int tempo_minimo[NUM_MAXIMO_TERMINAIS];      
    bool visitado[NUM_MAXIMO_TERMINAIS];     
    int predecessor[NUM_MAXIMO_TERMINAIS];      
    int caminho[NUM_MAXIMO_TERMINAIS];       

    for (int i = 0; i < NUM_MAXIMO_TERMINAIS; i++) {
        tempo_minimo[i] = TEMPO_MAXIMO;  
        visitado[i] = false;        
        predecessor[i] = -1;          
    }
    tempo_minimo[terminal_origem] = 0;   


    for (int passo = 0; passo < NUM_MAXIMO_TERMINAIS; passo++) {
        int tempo_mais_baixo = TEMPO_MAXIMO;
        int terminal_atual = -1;
        
        for (int t = 0; t < NUM_MAXIMO_TERMINAIS; t++) {
            if (!visitado[t] && tempo_minimo[t] < tempo_mais_baixo) {
                tempo_mais_baixo = tempo_minimo[t];
                terminal_atual = t;
            }
        }
        
        if (terminal_atual == -1) break;
        visitado[terminal_atual] = true;

        for (int vizinho = 0; vizinho < NUM_MAXIMO_TERMINAIS; vizinho++) {
            if (tempo[terminal_atual][vizinho] > 0 && !visitado[vizinho]) {
                int tempo_candidato = tempo_minimo[terminal_atual] + tempo[terminal_atual][vizinho];
                
                if (tempo_candidato < tempo_minimo[vizinho]) {
                    tempo_minimo[vizinho] = tempo_candidato;
                    predecessor[vizinho] = terminal_atual;
                }
            }
        }
    }

    if (tempo_minimo[terminal_destino] == TEMPO_MAXIMO) {
        printf("\nNão há conexão entre %s e %s\n", 
               terminais[terminal_origem], terminais[terminal_destino]);
        return;
    }

    printf("\nRota mais rápida de %s para %s:\n", 
           terminais[terminal_origem], terminais[terminal_destino]);
    
    int posicao = 0;
    int terminal_atual = terminal_destino;
    while (terminal_atual != -1) {
        caminho[posicao++] = terminal_atual;
        terminal_atual = predecessor[terminal_atual];
    }
    
    for (int i = posicao - 1; i >= 0; i--) {
        printf("%s", terminais[caminho[i]]);
        if (i > 0) printf(" → ");
    }
    printf("\nTempo total: %d minutos\n", tempo_minimo[terminal_destino]);
}

void melhor_rota_todos_terminais() {
    bool visitado[NUM_MAXIMO_TERMINAIS] = {false};
    int atual = 0;
    int rota[NUM_MAXIMO_TERMINAIS], tempo_total = 0;
    rota[0] = atual;
    visitado[atual] = true;

    for (int i = 1; i < NUM_MAXIMO_TERMINAIS; i++) {
        int menor_tempo = INT_MAX;
        int proximo = -1;

        for (int j = 0; j < NUM_MAXIMO_TERMINAIS; j++) {
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
    for (int i = 0; i < NUM_MAXIMO_TERMINAIS; i++) {
        printf("%s", terminais[rota[i]]);
        if (i != NUM_MAXIMO_TERMINAIS - 1) printf(" -> ");
    }
    printf("\nTempo total estimado: %d minutos\n", tempo_total);
}
void melhor_rota_menos_baldeacoes(int origem, int destino) {
    bool visitado[NUM_MAXIMO_TERMINAIS] = {false};
    int fila[NUM_MAXIMO_TERMINAIS];
    int anterior[NUM_MAXIMO_TERMINAIS];
    int inicio = 0, fim = 0;

    for (int i = 0; i < NUM_MAXIMO_TERMINAIS; i++) anterior[i] = -1;

    fila[fim++] = origem;
    visitado[origem] = true;

    while (inicio < fim) {
        int atual = fila[inicio++];

        if (atual == destino) break;

        for (int i = 0; i < NUM_MAXIMO_TERMINAIS; i++) {
            if (tempo[atual][i] > 0 && !visitado[i]) {
                fila[fim++] = i;
                visitado[i] = true;
                anterior[i] = atual;
            }
        }
    }

    int caminho[NUM_MAXIMO_TERMINAIS];
    int tam = 0, atual = destino;
    while (atual != -1) {
        caminho[tam++] = atual;
        atual = anterior[atual];
    }

    if (tam == 0 || caminho[tam - 1] != origem) {
        printf("Caminho não encontrado.\n");
        return;
    }

    printf("Caminho com menos baldeações (%d paradas):\n", tam - 1);
    for (int i = tam - 1; i >= 0; i--) {
        printf("%s", terminais[caminho[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}