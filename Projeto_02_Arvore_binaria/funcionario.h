#ifndef FUNCIONARIO_H
#define FUNCIONARIO_H

#include <stdio.h>

typedef struct funcionarios {
	int cod;
	char nome[50];
	float preco;
} TFunc;

// Imprime pizza
void imprime_func(TFunc *p);

// Cria pizza. Lembrar de usar free(pizza)
TFunc *funcionario(int cod, char *nome, float preco);

// Salva pizza no arquivo out, na posicao atual do cursor
void salva_funcionario(TFunc *p, FILE *out);

// Le uma pizza do arquivo in na posicao atual do cursor
// Retorna um ponteiro para pizza lida do arquivo
TFunc *le_func(FILE *in);

// Compara duas pizzas
// Retorna 1 se os valores dos atributos de ambos forem iguais
// e 0 caso contrario
int cmp_func(TFunc *p1, TFunc *p2);

// Retorna tamanho do registro que representa a pizza em bytes
int tamanho_func_bytes();

#endif
