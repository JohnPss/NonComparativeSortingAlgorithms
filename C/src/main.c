#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "data_structures.h"
#include "ratings_reader.h"
#include "radix_sort.h"
#include "converters.h"
#include "counting_sort.h"
#include "config.h"

const int VOLUMES_TESTE[] = {100, 1000, 10000, 100000, 1000000, 25000000};
const int NUM_VOLUMES = sizeof(VOLUMES_TESTE) / sizeof(VOLUMES_TESTE[0]);
const int NUM_REPETICOES = 10;

typedef struct
{
    double tempoTotal;
    int numElementos;
    int ordenadoCorretamente;
} ResultadoMedicao;

#ifdef _WIN32
#include <windows.h>
#include <psapi.h>
size_t getMemoryUsage()
{
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}
#elif defined(__linux__)
#include <unistd.h>
size_t getMemoryUsage()
{
    FILE *file = fopen("/proc/self/status", "r");
    if (!file)
        return 0;
    char line[128];
    size_t vmrss = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (sscanf(line, "VmRSS: %zu kB", &vmrss) == 1)
            break;
    }
    fclose(file);
    return vmrss * 1024;
}
#else
size_t getMemoryUsage() { return 0; }
#endif

size_t calculatePreciseMemoryUsage(TipoEstrutura tipo, int numElementos)
{
    if (numElementos <= 0)
        return 0;

    switch (tipo)
    {
    case LISTA_LINEAR:
        return (sizeof(int) * numElementos) + sizeof(LinearList);
    case LISTA_DINAMICA:
        return (sizeof(Node) * numElementos) + sizeof(LinkedList);
    case PILHA_LINEAR:
        return (sizeof(int) * numElementos) + sizeof(LinearStack);
    case PILHA_DINAMICA:
        return (sizeof(Node) * numElementos) + sizeof(Stack);
    case FILA_LINEAR:
        return (sizeof(int) * numElementos) + sizeof(LinearQueue);
    case FILA_DINAMICA:
        return (sizeof(Node) * numElementos) + sizeof(Queue);
    default:
        return 0;
    }
}

ResultadoMedicao medirDesempenho(TipoEstrutura tipo_estrutura, int maxLines)
{
    ResultadoMedicao resultado = {0.0, 0, 0};
    void *estrutura = NULL;
    int *array = NULL;
    clock_t inicio_total, fim_total;

    int numElementos = lerDados_PorTipo(&estrutura, tipo_estrutura, TIPO_DADO, maxLines);
    if (numElementos <= 0)
        return resultado;
    resultado.numElementos = numElementos;

    inicio_total = clock();
    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        array = linearListToArray((LinearList *)estrutura);
        break;
    case LISTA_DINAMICA:
        array = listToArray((LinkedList *)estrutura);
        break;
    case PILHA_LINEAR:
        array = linearStackToArray((LinearStack *)estrutura);
        break;
    case PILHA_DINAMICA:
        array = stackToArray((Stack *)estrutura);
        break;
    case FILA_LINEAR:
        array = linearQueueToArray((LinearQueue *)estrutura);
        break;
    case FILA_DINAMICA:
        array = queueToArray((Queue *)estrutura);
        break;
    }
    if (!array)
    {
        return resultado;
    }

    countingSort(array, numElementos);
    resultado.ordenadoCorretamente = isArraySorted(array, numElementos);

    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        destroyLinearList((LinearList *)estrutura);
        estrutura = arrayToLinearList(array, numElementos);
        break;
    case LISTA_DINAMICA:
        destroyList((LinkedList *)estrutura);
        estrutura = arrayToList(array, numElementos);
        break;
    case PILHA_LINEAR:
        destroyLinearStack((LinearStack *)estrutura);
        estrutura = arrayToLinearStack(array, numElementos);
        break;
    case PILHA_DINAMICA:
        destroyStack((Stack *)estrutura);
        estrutura = arrayToStack(array, numElementos);
        break;
    case FILA_LINEAR:
        destroyLinearQueue((LinearQueue *)estrutura);
        estrutura = arrayToLinearQueue(array, numElementos);
        break;
    case FILA_DINAMICA:
        destroyQueue((Queue *)estrutura);
        estrutura = arrayToQueue(array, numElementos);
        break;
    }

    fim_total = clock();
    resultado.tempoTotal = ((double)(fim_total - inicio_total)) / CLOCKS_PER_SEC * 1000;

    free(array);
    switch (tipo_estrutura)
    {
    case LISTA_LINEAR:
        destroyLinearList((LinearList *)estrutura);
        break;
    case LISTA_DINAMICA:
        destroyList((LinkedList *)estrutura);
        break;
    case PILHA_LINEAR:
        destroyLinearStack((LinearStack *)estrutura);
        break;
    case PILHA_DINAMICA:
        destroyStack((Stack *)estrutura);
        break;
    case FILA_LINEAR:
        destroyLinearQueue((LinearQueue *)estrutura);
        break;
    case FILA_DINAMICA:
        destroyQueue((Queue *)estrutura);
        break;
    }

    return resultado;
}

void exibirTabelaResumoFinal(double tempos[6][NUM_VOLUMES], size_t memorias[6][NUM_VOLUMES], const char *nomes[6])
{
    printf("\n\n");
    printf("                                         TABELA RESUMO FINAL\n");
    printf("============================================================================================================\n");

    printf("%-22s | %-10s |", "Estrutura", "Tipo");
    for (int i = 0; i < NUM_VOLUMES; i++)
    {
        printf(" %10d |", VOLUMES_TESTE[i]);
    }
    printf("\n------------------------------------------------------------------------------------------------------------\n");

    printf("\nTEMPO (ms):\n");
    for (int i = 0; i < 6; i++)
    {
        const char *tipo = (strstr(nomes[i], "Linear") != NULL) ? "linear" : "dynamic";
        printf("%-22s | %-10s |", nomes[i], tipo);
        for (int j = 0; j < NUM_VOLUMES; j++)
        {
            if (tempos[i][j] < 0)
            {
                printf(" %10s |", "FALHA");
            }
            else
            {
                printf(" %10.2f |", tempos[i][j]);
            }
        }
        printf("\n");
    }

    printf("\nMEMORIA (MB):\n");
    for (int i = 0; i < 6; i++)
    {
        const char *tipo = (strstr(nomes[i], "Linear") != NULL) ? "linear" : "dynamic";
        printf("%-22s | %-10s |", nomes[i], tipo);
        for (int j = 0; j < NUM_VOLUMES; j++)
        {
            if (memorias[i][j] == 0)
            {
                printf(" %10s |", "N/A");
            }
            else
            {
                double memoria_mb = memorias[i][j] / (1024.0 * 1024.0);
                printf(" %10.2f |", memoria_mb);
            }
        }
        printf("\n");
    }
    printf("============================================================================================================\n");
}

int main()
{
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                 ANÁLISE DE DESEMPENHO - ESTRUTURAS DE DADOS (LINGUAGEM C)                 ║\n");
    printf("║                                     COUNTING SORT                                     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf("📁 Arquivo: %s\n", ARQUIVO_ENTRADA);
    printf("📊 Volumes de teste: ");
    for (int i = 0; i < NUM_VOLUMES; i++)
        printf("%d ", VOLUMES_TESTE[i]);
    printf("\n");
    printf("🔄 Repetições por teste: %d\n\n", NUM_REPETICOES);

    TipoEstrutura estruturas[] = {LISTA_LINEAR, LISTA_DINAMICA, PILHA_LINEAR, PILHA_DINAMICA, FILA_LINEAR, FILA_DINAMICA};
    const int NUM_ESTRUTURAS = sizeof(estruturas) / sizeof(estruturas[0]);
    const char *nomesEstruturas[] = {"Lista Linear", "Lista Dinamica", "Pilha Linear", "Pilha Dinamica", "Fila Linear", "Fila Dinamica"};

    double resultadosTempo[NUM_ESTRUTURAS][NUM_VOLUMES];
    size_t resultadosMemoria[NUM_ESTRUTURAS][NUM_VOLUMES];

    for (int i = 0; i < NUM_ESTRUTURAS; i++)
    {
        for (int j = 0; j < NUM_VOLUMES; j++)
        {
            int volumeAtual = VOLUMES_TESTE[j];
            double somaTempos = 0.0;
            int testesBemSucedidos = 0;
            size_t memoriaAmostra = 0;

            printf("⏳ Testando %s com %d elementos (%d repetições)...", nomesEstruturas[i], volumeAtual, NUM_REPETICOES);
            fflush(stdout);

            for (int k = 0; k < NUM_REPETICOES; k++)
            {
                ResultadoMedicao res = medirDesempenho(estruturas[i], volumeAtual);

                if (res.ordenadoCorretamente)
                {
                    somaTempos += res.tempoTotal;
                    testesBemSucedidos++;
                    if (k == 0)
                    {
                        memoriaAmostra = calculatePreciseMemoryUsage(estruturas[i], res.numElementos);
                    }
                }
                else
                {
                    printf(" ❌ Erro na ordenação em uma das repetições para %s com %d elementos!\n", nomesEstruturas[i], volumeAtual);
                    somaTempos = -1.0;
                    memoriaAmostra = 0;
                    break;
                }
            }

            if (somaTempos != -1.0 && testesBemSucedidos > 0)
            {
                resultadosTempo[i][j] = somaTempos / testesBemSucedidos;
                resultadosMemoria[i][j] = memoriaAmostra;
                printf(" ✅ Concluído! Média: (%.2f ms)\n", resultadosTempo[i][j]);
            }
            else
            {
                resultadosTempo[i][j] = -1.0;
                resultadosMemoria[i][j] = 0;
                if (somaTempos != -1.0)
                {
                    printf(" ❌ Nenhuma repetição bem-sucedida para %s com %d elementos.\n", nomesEstruturas[i], volumeAtual);
                }
            }
        }
    }

    ResultadoMedicao resultadoTeste = medirDesempenho(PILHA_LINEAR, 100);
    resultadosTempo[2][0] = resultadoTeste.tempoTotal;
    resultadosMemoria[2][0] = calculatePreciseMemoryUsage(PILHA_LINEAR, resultadoTeste.numElementos);
    exibirTabelaResumoFinal(resultadosTempo, resultadosMemoria, nomesEstruturas);

    return 0;
}
