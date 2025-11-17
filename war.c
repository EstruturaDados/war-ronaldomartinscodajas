#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TERRITORIOS 5

// ------------------------- STRUCT --------------------------
typedef struct {
    char nome[20];
    int tropas;
} Territorio;

// ---------------------- FUNÇÃO DE ATAQUE -------------------
int simularAtaque(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nDado do Atacante: %d", dadoA);
    printf("\nDado do Defensor: %d\n", dadoD);

    // Empates favorecem o atacante
    if (dadoA >= dadoD) {
        defensor->tropas--;
        printf("➡️ Atacante venceu a rodada! Defensor perdeu 1 tropa.\n");
        return 1;
    } else {
        atacante->tropas--;
        printf("🛡️ Defensor venceu! Atacante perdeu 1 tropa.\n");
        return 0;
    }
}

// ------------------------- EXIBE MAPA -----------------------
void exibirMapa(Territorio *t) {
    printf("\n======= MAPA ATUAL =======\n");
    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        printf("%d - %-10s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].tropas);
    }
}

// --------------------------- MAIN ---------------------------
int main() {
    srand(time(NULL));

    // --------- ALOCAÇÃO DINÂMICA COM CALLOC ---------
    Territorio *mapa = (Territorio *) calloc(NUM_TERRITORIOS, sizeof(Territorio));

    // --------- CADASTRO DOS TERRITÓRIOS (NOVATO) ----------
    snprintf(mapa[0].nome, 20, "Colina");
    snprintf(mapa[1].nome, 20, "Deserto");
    snprintf(mapa[2].nome, 20, "Floresta");
    snprintf(mapa[3].nome, 20, "Mina");
    snprintf(mapa[4].nome, 20, "Vale");

    for (int i = 0; i < NUM_TERRITORIOS; i++) {
        mapa[i].tropas = rand() % 5 + 3; // 3 a 7 tropas
    }

    int opcao = 1;
    int a, d;

    printf("\n===== NÍVEL AVENTUREIRO: BATALHAS ESTRATÉGICAS =====\n");

    while (opcao != 0) {
        exibirMapa(mapa);

        printf("\n1 - Atacar\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            printf("\nEscolha território ATACANTE (1-5): ");
            scanf("%d", &a);

            printf("Escolha território DEFENSOR (1-5): ");
            scanf("%d", &d);

            a--; d--;

            if (a == d) {
                printf("❌ Um território não pode atacar ele mesmo.\n");
                continue;
            }

            if (mapa[a].tropas <= 1) {
                printf("❌ Tropas insuficientes para atacar.\n");
                continue;
            }

            printf("\n⚔️ Batalha entre %s e %s!\n",
                   mapa[a].nome, mapa[d].nome);

            simularAtaque(&mapa[a], &mapa[d]);

            // ----------- CONQUISTA DE TERRITÓRIO -----------
            if (mapa[d].tropas <= 0) {
                printf("\n🏆 O território %s foi CONQUISTADO!\n", mapa[d].nome);
                mapa[d].tropas = 1;
                mapa[a].tropas--;
            }
        }
    }

    free(mapa);
    printf("\nJogo encerrado!\n");

    return 0;
}
