#include <stdio.h>
#include <stdlib.h>

#define SENTINELA 2147483647

typedef struct registros
{
	int chave;

} Registro;

typedef struct fila
{
	char *nome_arquivo;
	struct fila *prox;

} Fila;

typedef struct noVenc
{
	int    vencedor;
	int	   indice;
	FILE  *end_vencedor;
	struct noVenc *pai;
	struct noVenc *esq;
	struct noVenc *dir;

} NoVenc;

void adicionaArquivo(Fila **fila,char *arquivo);
char* popArquivo(Fila **fila);

