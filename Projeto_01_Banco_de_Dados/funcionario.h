#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



typedef struct Funcionario {
    int cod;
    char nome[50];
    char cpf[15];
    char data_nascimento[11];
    double salario;
} TFunc;

// Imprime funcionario
void imprime(TFunc *func);

// Cria funcionario. Lembrar de usar free(funcionario)
TFunc *funcionario(int cod, char *nome, char *cpf, char *data_nascimento, double salario);

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(TFunc *func, FILE *out);

// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
TFunc *le(FILE *in);

// Retorna tamanho do funcionario em bytes
int tamanho();

void limpa();

int tamanho_registro();

void salvar_resultados_BS(TFunc *func, int comp, float tempo);

void salvar_resultados_Bin(TFunc *func, int comp, float tempo);

void insere_5_funcionarios(FILE *out);

void Insere_5000_funcio (FILE *out);

void cria_base_de_dados(FILE *arq, int nFunc);

void IntercalaOtima(FILE *arq  , int maxss ,char *nome_ordenado );

TFunc *busca_binaria_CT(int chave, FILE *in, int inicio, int fim);

TFunc *busca_sequencial_CT(int chave, FILE *in, int tamanho_arquivo);

void insertion_sort_disco(FILE *arq, int tam);

void intercalateFiles(char *inputFilenames[], int numFiles, char *outputFilename);

#endif // FUNCIONARIO_H_INCLUDED
