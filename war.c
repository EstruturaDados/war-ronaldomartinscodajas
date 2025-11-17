#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define NUM_TERR 5

#define MISSAO_DESTRUIR 1
#define MISSAO_CONQUISTAR 2

// ---------------------- STRUCT --------------------------
typedef struct {
    char nome[20];
    char cor[20];
    int tropas;
} Territorio;

// ---------------------- PROTÓTIPOS -----------------------
void inicializarTerritorios(Territorio *mapa);
void exibirMapa(const Territorio *mapa);
void exibirMissao(int missao);
int menu();
int escolherTerritorio(const char *msg);
int simularAtaque(Territorio *a, Territorio *d);
int gerarMissao();
int verificarMissao(int missao, const Territorio *mapa, int conquistas);

// ---------------------------------------------------------

void inicializarTerritorios(Territorio *mapa) 
{
    const char *nomes[] = {"America", "Europa", "Asia", "Africa", "Oceania"};
    const char *cores[] = {"Verde", "Azul", "Vermelho", "Amarelo", "Branco"};
    int tropasFixas[]   = {5, 3, 2, 4, 1};  // Igual ao print

    for (int i = 0; i < NUM_TERR; i++) {
        snprintf(mapa[i].nome, 20, "%s", nomes[i]);
        snprintf(mapa[i].cor, 20, "%s", cores[i]);
        mapa[i].tropas = tropasFixas[i];
    }
}

void exibirMapa(const Territorio *mapa) 
{
    printf("\n============= MAPA DO MUNDO =============\n");

    for (int i = 0; i < NUM_TERR; i++) {
        printf("%d. %-10s (Exercito: %-8s , Tropas: %d)\n",
               i + 1,
               mapa[i].nome,
               mapa[i].cor,
               mapa[i].tropas
        );
    }

    printf("=========================================\n");
}

void exibirMissao(int missao)
{
    printf("\n--- SUA MISSAO (Exercito Azul) ---\n");

    if (missao == MISSAO_DESTRUIR)
        printf("Destruir o exercito Verde.\n");
    else
        printf("Conquistar 3 territorios.\n");
}

int menu() 
{
    int op;
    printf("\n--- MENU DE ACOES ---\n");
    printf("1 - Atacar\n");
    printf("2 - Verificar Missao\n");
    printf("0 - Sair\n");
    printf("Escolha sua acao: ");
    scanf("%d", &op);
    return op;
}

int escolherTerritorio(const char *msg)
{
    int t;
    printf("%s (1-5): ", msg);
    scanf("%d", &t);
    return t - 1;
}

int simularAtaque(Territorio *a, Territorio *d)
{
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\n🎲 Dado Atacante: %d", dadoA);
    printf("\n🛡️  Dado Defensor: %d\n", dadoD);

    if (dadoA >= dadoD) {
        d->tropas--;
        printf("➡️ Atacante venceu a rodada!\n");
        return 1;
    } else {
        a->tropas--;
        printf("🛡️ Defensor venceu a rodada!\n");
        return 0;
    }
}

int gerarMissao()
{
    return MISSAO_DESTRUIR;   // Pode trocar para sorteio aleatório: (rand()%2)+1
}

int verificarMissao(int missao, const Territorio *mapa, int conquistas)
{
    if (missao == MISSAO_DESTRUIR) {
        // Missão = destruir o exército VERDE
        for (int i = 0; i < NUM_TERR; i++) {
            if (strcmp(mapa[i].cor, "Verde") == 0 && mapa[i].tropas <= 0)
                return 1;
        }
    }

    if (missao == MISSAO_CONQUISTAR) {
        if (conquistas >= 3)
            return 1;
    }

    return 0;
}

// ==========================================================
// =========================== MAIN ==========================
// ==========================================================

int main() 
{
    srand(time(NULL));

    Territorio mapa[NUM_TERR];
    inicializarTerritorios(mapa);

    int conquistas = 0;
    int missao = gerarMissao();

    printf("\n===== WAR ESTRUTURADO - NIVEL MESTRE =====\n");
    exibirMissao(missao);

    int op = 1;
    while (op != 0) {

        exibirMapa(mapa);
        op = menu();

        if (op == 1) {

            int a = escolherTerritorio("Escolha territorio ATACANTE");
            int d = escolherTerritorio("Escolha territorio DEFENSOR");

            if (a < 0 || a >= NUM_TERR || d < 0 || d >= NUM_TERR) {
                printf("❌ Territorio invalido!\n");
                continue;
            }

            if (a == d) {
                printf("❌ Um territorio nao pode atacar ele mesmo.\n");
                continue;
            }

            if (mapa[a].tropas <= 1) {
                printf("❌ Tropas insuficientes para atacar.\n");
                continue;
            }

            printf("\n⚔️ Batalha entre %s (%s) e %s (%s)!\n",
                   mapa[a].nome, mapa[a].cor,
                   mapa[d].nome, mapa[d].cor);

            simularAtaque(&mapa[a], &mapa[d]);

            if (mapa[d].tropas <= 0) {
                printf("\n🏆 TERRITORIO %s CONQUISTADO!\n", mapa[d].nome);
                mapa[d].tropas = 1;
                mapa[a].tropas--;
                conquistas++;
            }

            if (verificarMissao(missao, mapa, conquistas)) {
                printf("\n🎉🎉🎉 MISSAO CUMPRIDA! PARABENS, COMANDANTE! 🎉🎉🎉\n");
                break;
            }
        }

        else if (op == 2) {
            exibirMissao(missao);
            if (verificarMissao(missao, mapa, conquistas))
                printf("\n✔️ Missao ja concluida!\n");
            else
                printf("\n❗ Missao ainda nao concluida.\n");
        }
    }

    printf("\nJogo encerrado!\n");
    return 0;
}
