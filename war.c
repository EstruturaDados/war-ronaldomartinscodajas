#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Constante para o número de territórios
#define NUM_TERRITORIOS 5

// 1. Struct Territorio
typedef struct {
    char nome[50];
    char cor_exercito[20];
    int num_tropas;
} Territorio;

// Função auxiliar para limpar a entrada (necessária após scanf antes de fgets)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para ler os dados de um território, replicando o formato do terminal
void cadastrar_territorio(Territorio *t, int id) {
    printf("--- Cadastrando Territorio %d ---\n", id);
    
    // Leitura do Nome (usando fgets)
    printf("Nome do Territorio: ");
    if (fgets(t->nome, sizeof(t->nome), stdin) != NULL) {
        // Remove o '\n' que o fgets adiciona
        t->nome[strcspn(t->nome, "\n")] = 0;
    }
    
    // Leitura da Cor do Exército
    printf("Cor do Exercito (ex: Azul, Verde): ");
    // Note: usamos %19s, mas é crucial que o usuário digite 'Azul' ou 'Verde' na linha
    scanf("%19s", t->cor_exercito); 
    
    // Leitura do Número de Tropas
    printf("Numero de Tropas: ");
    scanf("%d", &t->num_tropas);
    
    // Limpa o buffer de entrada para a próxima chamada de fgets
    limpar_buffer();
}

// Função para exibir o estado atual do mapa (Saída exigida pelo nível)
void exibir_mapa(Territorio mapa[], int tamanho) {
    printf("\n\n==================================================\n");
    printf("=== 🌍 Estado Atual do Mapa Inicial ===\n");
    printf("| %-4s | %-20s | %-10s | %-6s |\n", "ID", "Territorio", "Exercito", "Tropas");
    printf("|------|----------------------|------------|--------|\n");
    
    for (int i = 0; i < tamanho; i++) {
        printf("| %-4d | %-20s | %-10s | %-6d |\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor_exercito, 
               mapa[i].num_tropas);
    }
    printf("==================================================\n\n");
}

int main() {
    // 2. Vetor estático de 5 elementos
    Territorio mapa[NUM_TERRITORIOS];
    
    // Reproduzindo o cabeçalho da imagem
    printf("==================================================\n");
    printf("Vamos cadastrar os %d territorios iniciais do nosso mundo.\n\n", NUM_TERRITORIOS);
    
    // O primeiro loop precisa de uma limpeza inicial se o terminal já tiver um \n pendente
    limpar_buffer();
    
    // 3. Loop de cadastro para os 5 territórios
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        cadastrar_territorio(&mapa[i], i + 1);
        printf("\n"); // Linha em branco para separar os cadastros, como na imagem
    }
    
    // 4. Exibir o estado atual do mapa
    exibir_mapa(mapa, NUM_TERRITORIOS);
    
    return 0;
}