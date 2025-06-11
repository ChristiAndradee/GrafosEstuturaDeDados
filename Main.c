#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define NUM_MAXIMO_TERMINAIS 11
#define TEMPO_MAXIMO 9999

char terminais[NUM_MAXIMO_TERMINAIS][50] = {
    "Boqueirao", "CIC", "Pinheirinho", "Cabral", "Guadalupe",
    "Capao Raso", "Santa Candida", "Fazendinha", "Campo Comprido", "Hauer"
};

int tempo[NUM_MAXIMO_TERMINAIS][NUM_MAXIMO_TERMINAIS] = {
    {0, 10, 15, 0, 0, 20, 0, 0, 0, 25}, // Boqueirao
    {10, 0, 5, 0, 0, 15, 0, 10, 0, 0}, // CIC
    {15, 5, 0, 0, 0, 5, 0, 0, 20, 0}, // Pinheirinho
    {0, 0, 0, 0, 10, 0, 5, 0, 0, 0}, // Cabral
    {0, 0, 0, 10, 0, 0, 0, 0, 0, 5}, // Guadalupe
    {20, 15, 5, 0, 0, 0, 0, 10, 0, 0}, // Capao Raso
    {0, 0, 0, 5, 0, 0, 0, 15, 0, 0}, // Santa Candida
    {0, 10, 0, 0, 0, 10, 15, 0, 10, 0}, // Fazendinha
    {0, 0, 20, 0, 0, 0, 0, 10, 0, 5}, // Campo Comprido
    {25, 0, 0, 0, 5, 0, 0, 0, 5, 0} // Hauer
};

int num_terminais = 10;

void menu();
void melhor_rota_menos_tempo(int terminal_origem, int terminal_destino);
void melhor_rota_todos_terminais();
void listar_terminais();
void melhor_rota_menos_baldeacoes(int origem, int destino);
void adicionar_terminal();

int main() {
    menu();
    return 0;
}

void listar_terminais() {
    printf("\nTerminais disponiveis:\n");
    for (int i = 0; i < num_terminais; i++) {
        printf("%d. %s\n", i, terminais[i]);
    }
}

void adicionar_terminal() {
    if (num_terminais >= NUM_MAXIMO_TERMINAIS) {
        printf("Limite maximo de terminais atingido.\n");
        return;
    }

    char nome[50];
    printf("Digite o nome do novo terminal: ");
    getchar(); // limpar buffer
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0; // remover newline

    strcpy(terminais[num_terminais], nome);

    printf("Digite o tempo entre '%s' e os demais terminais existentes (em minutos, 0 se nao ha conexao):\n", nome);
    for (int i = 0; i < num_terminais; i++) {
        printf("Tempo ate '%s': ", terminais[i]);
        scanf("%d", &tempo[num_terminais][i]);
        tempo[i][num_terminais] = tempo[num_terminais][i]; // simetria
    }

    num_terminais++;
    printf("Terminal '%s' adicionado com sucesso!\n", nome);
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
        printf("4. Adicionar novo terminal\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                listar_terminais();
                printf("\nDigite o numero do terminal de origem: ");
                scanf("%d", &origem);
                printf("Digite o numero do terminal de destino: ");
                scanf("%d", &destino);
                melhor_rota_menos_tempo(origem, destino);
                break;

            case 2:
                listar_terminais();
                printf("\nDigite o numero do terminal de origem: ");
                scanf("%d", &origem);
                printf("Digite o numero do terminal de destino: ");
                scanf("%d", &destino);
                melhor_rota_menos_baldeacoes(origem, destino);
                break;

            case 3:
                melhor_rota_todos_terminais();
                break;

            case 4:
                adicionar_terminal();
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

    for (int i = 0; i < num_terminais; i++) {
        tempo_minimo[i] = TEMPO_MAXIMO;  
        visitado[i] = false;        
        predecessor[i] = -1;          
    }
    tempo_minimo[terminal_origem] = 0;   

    for (int passo = 0; passo < num_terminais; passo++) {
        int tempo_mais_baixo = TEMPO_MAXIMO;
        int terminal_atual = -1;
        
        for (int t = 0; t < num_terminais; t++) {
            if (!visitado[t] && tempo_minimo[t] < tempo_mais_baixo) {
                tempo_mais_baixo = tempo_minimo[t];
                terminal_atual = t;
            }
        }
        
        if (terminal_atual == -1) break;
        visitado[terminal_atual] = true;

        for (int vizinho = 0; vizinho < num_terminais; vizinho++) {
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
        printf("\nNao ha conexao entre %s e %s\n", 
               terminais[terminal_origem], terminais[terminal_destino]);
        return;
    }

    printf("\nRota mais rapida de %s para %s:\n", 
           terminais[terminal_origem], terminais[terminal_destino]);
    
    int posicao = 0;
    int terminal_atual = terminal_destino;
    while (terminal_atual != -1) {
        caminho[posicao++] = terminal_atual;
        terminal_atual = predecessor[terminal_atual];
    }
    
    for (int i = posicao - 1; i >= 0; i--) {
        printf("%s", terminais[caminho[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\nTempo total: %d minutos\n", tempo_minimo[terminal_destino]);
}

void melhor_rota_todos_terminais() {
    bool visitado[NUM_MAXIMO_TERMINAIS] = {false};
    int atual = 0;
    int rota[NUM_MAXIMO_TERMINAIS], tempo_total = 0;
    rota[0] = atual;
    visitado[atual] = true;

    for (int i = 1; i < num_terminais; i++) {
        int menor_tempo = INT_MAX;
        int proximo = -1;

        for (int j = 0; j < num_terminais; j++) {
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

    printf("\n[Melhor Caminho para Visitar Todos os Terminais - Aprox Vizinho Mais Proximo]:\n");
    for (int i = 0; i < num_terminais; i++) {
        printf("%s", terminais[rota[i]]);
        if (i != num_terminais - 1) printf(" -> ");
    }
    printf("\nTempo total estimado: %d minutos\n", tempo_total);
}

void melhor_rota_menos_baldeacoes(int origem, int destino) {
    bool visitado[NUM_MAXIMO_TERMINAIS] = {false};
    int fila[NUM_MAXIMO_TERMINAIS];
    int anterior[NUM_MAXIMO_TERMINAIS];
    int inicio = 0, fim = 0;

    for (int i = 0; i < num_terminais; i++) anterior[i] = -1;

    fila[fim++] = origem;
    visitado[origem] = true;

    while (inicio < fim) {
        int atual = fila[inicio++];

        if (atual == destino) break;

        for (int i = 0; i < num_terminais; i++) {
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
        printf("Caminho nao encontrado.\n");
        return;
    }

    printf("Caminho com menos baldeacoes (%d paradas):\n", tam - 1);
    for (int i = tam - 1; i >= 0; i--) {
        printf("%s", terminais[caminho[i]]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}
