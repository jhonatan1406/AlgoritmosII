#ifndef HASHEMDISCO_H_INCLUDED
#define HASHEMDISCO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TAM 100
#define MAX_SIZE 100 // tamanho máximo da tabela hash

typedef struct {
    int cod;
    float salario;
    char nome[50];
} TFunc; // estrutura que contém as informações do funcionário

typedef struct elemento {
    int chave;
    TFunc *valor;
    struct elemento *prox;
} Elemento;


// estrutura para representar um nó da lista encadeada
typedef struct no {
    TFunc *dado;
    struct no *prox;
} TNo;

// estrutura para representar uma lista encadeada
typedef struct lista {
    TNo *inicio;
    TNo *fim;
} TLista;


typedef struct {
    Elemento **tabela;
    int tamanho;
} THash; // tabela de hash


Elemento* novoElemento(int chave, TFunc *valor);

THash* novaTabelaHash(int tamanho);

int hash(int chave);

void inserir(THash *t, int chave, TFunc *valor);

TFunc* buscar(THash *t, int chave);

void imprimir(THash *t);

TFunc *funcionario(int cod, char *nome, double salario);

void inserir_funcionarios(THash *t);

void remover_funcionario(THash *t, int cod);

void buscar_funcionario(THash *t, int cod);

void limpar_tabela(THash *t);

void salvarHash(THash *t, FILE *arquivo);

void inserirBusca(TFunc *valor, char* nome_arquivo);


#endif // HASHEMDISCO_H_INCLUDED
