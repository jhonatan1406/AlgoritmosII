
#include "geracao_particoes.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>
#include <time.h>
void selecao_com_substituicao(char *nome_arq_entrada, Nomes *nome_aqrs_saida, int M)
{

    int fim = 0; // vari�vel de controle para saber se arquivo de entrada terminou
    FILE *arq;   // declara o ponteiro p/ arquivo de entrada

    // abre o arq para leitura
    if ((arq = fopen(nome_arq_entrada, "rb")) == NULL)
    {
        printf("[ERRO 3] nao foi possivel abrir o arquivo");
    }
    else
    {

        FILE *p; // arq de parti��es

        TFunc *memory[M]; // array em memoria
        char frozen[M];   // array de congelados
        initFronzenArray(frozen, M);

        // le os primeiros M registros
        int z = 0;
        while (!feof(arq) && z < M)
        {
            memory[z] = le(arq);
            z++;
        }

        while (fim == 0)
        { // enquanto nao for o fim do arquivo de entrada
            // abre arquivo de parti��o
            char *nome_particao = nome_aqrs_saida->nome; // pega o nome da primeira parti��o

            if ((p = fopen(nome_particao, "wb")) == NULL)
            {
                printf("[ERRO 2] nao foi possivel criar arquivo de saida");
            }
            else
            {
                while ((fullXFrozenArray(frozen, M) != 1))
                {
                    // enquanto nao tiver todo o array congelado ou for o fim do arquivo, pega o index do menor codigo dentro da memory
                    int minIndex = getMinIndexWithFrozen(M, memory, frozen);

                    // salva na parti��o
                    TFunc *minFunc = memory[minIndex]; // minFunc fica como ultimo cliente salvo na parti��o
                    salva(minFunc, p);

                    // Pega o proximo registro
                    if (fim == 0) // Verifica se esta no final do arq de entrada, se estiver o alg nao carregara novos funcionarios
                    {
                        TFunc *minFuncAux = le(arq);
                        if (minFuncAux != NULL)
                        {
                            memory[minIndex] = minFuncAux;
                        }
                        else
                        {
                            // quando o funcionario carregado for null � porque ja esta no final do arquivo, entao ele gela a posi��o
                            fim = 1;
                            frozen[minIndex] = 'X';
                        }
                    }
                    else
                    {
                        frozen[minIndex] = 'X';
                    }

                    if (frozen[minIndex] != 'X')
                    {
                        // faz com q o alg nao seja quebrado quando na memory ja tiver clientes com NULL
                        if (memory[minIndex]->cod < minFunc->cod)
                        {
                            frozen[minIndex] = 'X';
                        }
                    }
                }

                fclose(p);                   // fecha parti��o
                initFronzenArray(frozen, M); // descongela

                nome_aqrs_saida = nome_aqrs_saida->prox; // pega o proximo nome de parti��o e coloca como atual
            }
        }
    }
    fclose(arq);
}

void selecao_natural(char *nome_arq_entrada, Nomes *nome_arqs_saida, int M, int n)
{
    // Vars de controle para saber se o arq de entrada terminou/ fim
    int indexReservatorio = 0, isEmptyEntrada = 0, fimParticao = 0;
    ;

    FILE *arq;          // ponteiro para arq de entrada
    FILE *reservatorio; // ponteiro para arq reservatorio

    // abre o arquivo para leitura
    arq = fopen(nome_arq_entrada, "rb");
    if (arq == NULL)
    {
        printf("[ERRO 1] - Nao foi possivel ler o arquivo\n");
    }
    else
    {
        FILE *p; // arq de parti��es

        TFunc *memory[M]; // array em memoria

        // Le os M primeiros registros
        int z = 0;
        while (!feof(arq) && z < M)
        {
            memory[z] = le(arq);
            z++;
        }

        while ((isEmptyEntrada == 0 && estaVazio(memory, M) == 0))
        { // enquanto nao for o fim do arquivo de entrada e fim do algoritmo(array_memory vazio)
            reservatorio = fopen("reservatorio.dat", "wb+");
            // abre arquivo de parti��o
            char *nome_particao = nome_arqs_saida->nome; // pega o nome da primeira parti��o
            if ((p = fopen(nome_particao, "wb")) == NULL)
            {
                printf("[ERRO 2] - Nao foi possivel criar arquivo de saida\n");
            }
            else
            {
                fimParticao = 0;
                while (fimParticao == 0)
                { // enquanto nao tiver todo o array NULL ou for o fim do arquivo
                    if (estaVazio(memory, M) == 1 || indexReservatorio > 5 || isEmptyEntrada != 0)
                    {
                        fimParticao = 1;
                    }
                    if (fimParticao == 1)
                    { // esvazia a memoria
                        while (estaVazio(memory, M) != 1)
                        {
                            int minIndex = getMinIndex(M, memory);
                            salva(memory[minIndex], p);
                            memory[minIndex] = NULL;
                        }
                        break;
                    }
                    // pega o index do menor codigo dentro da memoria
                    int minIndex = getMinIndex(M, memory);

                    // salva na parti��o
                    TFunc *minFunc = memory[minIndex]; // minFunc fica como ultimo cliente salvo na parti��o
                    salva(minFunc, p);
                    memory[minIndex] = NULL;

                    // Pega o proximo registro
                    if (isEmptyEntrada == 0)
                    { // se estiver puxando funcionarios NULL
                        TFunc *minFuncNovoR;
                        do
                        {
                            if (indexReservatorio > 5)
                            {
                                break;
                            }
                            minFuncNovoR = le(arq);
                            if (minFuncNovoR != NULL)
                            {
                                if (minFuncNovoR->cod < minFunc->cod)
                                {
                                    salva(minFuncNovoR, reservatorio); // se o cod de minFuncNovoR for menor que o func atual, guarda o minFuncNovoR no reservatorio (semelhante a congelar-lo)
                                    indexReservatorio++; // indica quantos elementos estao dentro do reservatorio
                                }
                                else
                                {
                                    memory[minIndex] = minFuncNovoR; // guarda o minFunNovoR na memoria, deixando-a ordenada
                                }
                            }
                            else
                            {
                                //fim do arquivo
                                isEmptyEntrada = 1;
                                memory[minIndex] = NULL;
                                break;
                            }
                        } while (minFuncNovoR->cod < minFunc->cod);
                    }
                }
                indexReservatorio = reservatorioTransferToMemory(reservatorio, memory, indexReservatorio, M);
                // Transfere os arquivos do reservatorio para a memoria para passarem pelas etapas novamente
                fclose(reservatorio);
                fclose(p);                               // fecha a parti��o atual
                nome_arqs_saida = nome_arqs_saida->prox; // pega o proximo nome de parti��o e o coloca como atual
            }
        }
        if ((isEmptyEntrada != 0) && (estaVazio(memory, M) == 0))
        {
            char *nome_particao = nome_arqs_saida->nome;
            if ((p = fopen(nome_particao, "wb")) == NULL)
            {
                printf("[ERRO 3] - nao foi possivel criar arquivo de saida\n");
            }
            else
            {
                while (estaVazio(memory, M) != 1)
                {
                    int minIndex = getMinIndex(M, memory);
                    salva(memory[minIndex], p);
                    memory[minIndex] = NULL;
                }
                fclose(p);
            }
        }
    }

    fclose(arq);
}

void initFronzenArray(char *array, int M)
{
	int i;
    for ( i = 0; i < M; i++)
    {
        array[i] = '0';
    }
}

int fullXFrozenArray(char *array, int m)
{
    int countX = 0;
    int i;
    for ( i = 0; i < m; i++)
    {
        if (array[i] == 'X')
        {
            countX++;
        }
    }
    return countX == m ? 1 : 0;
}

int getMinIndexWithFrozen(int M, TFunc **memory, char *frozen)
{
    int minIndex, first = 0;
    int k ;

    for ( k = 0; k < M;)
    {
        if (frozen[k] == 'X')
        {
            k++;
            continue;
        }
        if (first == 0)
        {
            minIndex = k;
            first++;
        }

        if (memory[k]->cod < memory[minIndex]->cod)
        {
            minIndex = k;
        }
        k++;
    }
    return minIndex;
}

int estaVazio(TFunc **vetor, int n)
{
	int i;
    for ( i = 0; i < n; i++)
    {
        if (vetor[i] != NULL)
            return 0;
    }
    return 1;
}


int reservatorioTransferToMemory(FILE *reservatorio, TFunc **memory, int indexReservatorio, int M)
{
    rewind(reservatorio);
    TFunc *aux = NULL;
    int i = 0;
    while ((aux = le(reservatorio)) != NULL && i < M)
    {
        memory[i] = aux;
        indexReservatorio--;
        i++;
    }
    // rewind(reservatorio);
    return indexReservatorio;
}

int getMinIndex(int M, TFunc **memory)
{

    int minIndex, first = 0;
	int k ;
    for ( k = 0; k < M;)
    {
        if (memory[k] == NULL)
        {
            k++;
            continue;
        }
        if (first == 0)
        {
            minIndex = k;
            first++;
        }

        if (memory[k]->cod < memory[minIndex]->cod)
        {
            minIndex = k;
        }
        k++;
    }
    return minIndex;
}



void selec_sub(){
    printf("\n Gerando particoes com SELECAO_SUBSTITUICAO...\n");
    clock_t inicio_tempo = clock();
    char *nomes=NULL;

    nomes = cria_nomes(cria_str("p1.dat"),
                       cria_nomes(cria_str("p2.dat"),
                                  cria_nomes(cria_str("p3.dat"),
                                             cria_nomes(cria_str("p4.dat"),
                                                        cria_nomes(cria_str("p5.dat"),
                                                                   cria_nomes(cria_str("p6.dat"),
                                                                              cria_nomes(cria_str("p7.dat"),
                                                                                         cria_nomes(cria_str("p8.dat"),
                                                                                                    cria_nomes(cria_str("p9.dat"), NULL)))))))));

    selecao_com_substituicao("funcionario.dat", nomes, 6);
    clock_t fim_tempo = clock();
    float tempo_gasto = (float)(fim_tempo - inicio_tempo) / CLOCKS_PER_SEC;

    printf("\nParticoes geradas com sucesso !!\n");
    printf("tempo gasto; %f", tempo_gasto);
}

